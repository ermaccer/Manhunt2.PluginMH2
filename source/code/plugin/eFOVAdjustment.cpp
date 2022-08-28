#include "..\manhunt2\core.h"
#include "..\manhunt2\Scene.h"
#include "..\manhunt2\Player.h"
#include "eFOVAdjustment.h"
#include "..\CSettingsManager.h"

void __declspec(naked) FOV_Hook()
{
	static int jmp_continue = 0x5AE9D5;
	static float newVal = SettingsMgr->fFOVFactor;

	_asm {
		pushad
		fld newVal
		fstp ds : 0x788C4C
		popad
		jmp jmp_continue
	}
}

void __declspec(naked) FOV_Hook2()
{
	static int jmp_continue = 0x5AEC36;
	static float newVal = SettingsMgr->fFOVFactor;
	static CPlayer* plr;
	_asm 	pushad

	plr = (CPlayer*)CScene::FindPlayer();

	if (!plr->isCrawling())
	{
		_asm {
			fld newVal
			fstp ds : 0x788C4C
			popad
			jmp jmp_continue
		}
	}
	else
	{
		_asm {
			fstp ds : 0x788C4C
			popad
			jmp jmp_continue
		}
	}

}


void eFOVAdjustment::Init()
{
	Nop(0x5AE9CD, 8);
	InjectHook(0x5AE9CD, FOV_Hook, PATCH_JUMP);

	Nop(0x5AEC30, 6);
	InjectHook(0x5AEC30, FOV_Hook2, PATCH_JUMP);
}
