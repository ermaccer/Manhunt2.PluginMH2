#include "eFirstPerson.h"
#include "..\manhunt2\core.h"
#include "..\manhunt2\Scene.h"
#include "..\manhunt2\Player.h"
#include "..\CSettingsManager.h"
#include "..\manhunt2\Vector.h"
#include <iostream>

bool eFirstPerson::m_bUnlockCamera = false;

void SetCamPos(CVector* dst, CVector* src, CVector* adj)
{
	static CVector offset = { 0.0f,-0.08f, 0.0 };
	CVector headPos = {};

	CPlayer* plr = (CPlayer*)CScene::FindPlayer();

	if (plr && !plr->isCrawling())
	{
		int head = plr->GetBoneFrame(1001);

		if (head)
		{
			headPos = *(CVector*)(head + 176);

			headPos.x += offset.x;
			headPos.y -= (adj->y + offset.y);
			headPos.z += offset.z;
		}

		dst->x = headPos.x + adj->x;
		dst->y = headPos.y + adj->y;
		dst->z = headPos.z + adj->z;;
	}
	else
	{
		dst->x = src->x + adj->x;
		dst->y = src->y + adj->y;
		dst->z = src->z + adj->z;
	}

}

void eFirstPerson::_null()
{
}

void eFirstPerson::Init()
{		
	// disable reset
	InjectHook(0x598EC3, _null, PATCH_CALL);
	// cam movement
	InjectHook(0x5AC38E, LookaroundHook, PATCH_JUMP);
	Nop(0x598E7B, 8);

	// disable player hide
	Nop(0x598E9A, 7);

	// disable weird resets
	Nop(0x5AB939, 6);

	// move cam forward a little
	Patch<float>(0x6D0C4C, 0.165f);

	InjectHook(0x5B1E66, SetCamPos);

	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(InputThread), nullptr, 0, nullptr);
}

void eFirstPerson::LookaroundUpdate()
{
	CPlayer* plr = (CPlayer*)CScene::FindPlayer();

	// could be done better probably
	if (((plr->GetPlayerFlags() & 0x40)
		&& !(plr->IsExecuting()))
			&& !m_bUnlockCamera)
	{
		Patch<short>(0x5AC3A7, 0x840F);
		Patch<int>(0x5AC3A9, 0xA4);
		if (SettingsMgr->bFirstPersonAutoResetCamera)
			plr->StartLookAround();
	}
	else
	{
		if (!(plr->GetCurrentWeaponSlot() == 4) || m_bUnlockCamera)
			Nop(0x5AC3A7, 6);
	}

}

void __declspec(naked) eFirstPerson::LookaroundHook()
{
	static int jmp_continue = 0x5AC393;
	_asm {
		pushad
		call LookaroundUpdate
		popad
		test    eax, 0x40000
		jmp jmp_continue
	}
}

void eFirstPerson::InputThread()
{
	while (true)
	{
		if (GetAsyncKeyState(SettingsMgr->iFirstPersonCameraUnlockKey) & 0x8000)
			m_bUnlockCamera = true;
		else
			m_bUnlockCamera = false;

		Sleep(1);
	}

}
