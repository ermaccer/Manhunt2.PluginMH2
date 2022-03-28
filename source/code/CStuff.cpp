#include "..\pch.h"
#include "CStuff.h"
#include "CSettingsManager.h"
#include "..\MemoryMgr.h"
#include "mh2.h"

int __fastcall CStuff::HookIsFirearm(int ptr)
{
	return 0;
}

int __fastcall CStuff::HookCheckExecutionWeaponType(int ptr)
{
	return 0;
}

void CStuff::HookSetMaxNumberOfRats()
{
	Memory::VP::Patch<int>(0x7942B4, 32);
}

void CStuff::HeapGeneration()
{
	if (SettingsMgr->iStreamingMemory > 0)
	{
		if (SettingsMgr->iStreamingMemory > 512)
			SettingsMgr->iStreamingMemory = 512;
		int size = SettingsMgr->iStreamingMemory * 1024 * 1024;
		int* ptr = *(int**)0x76CF00;
	    CallMethod<0x580700, int*, int>(ptr, size);

	}

}

void __declspec(naked) CStuff::DisableExecutionCamera()
{
	static int jmpContinue = 0x5B2637;
	static int jmpFail = 0x5B2B6F;
	if (GetHunterAboutToBeExecuted())
	{
		_asm {
			jmp jmpFail
		}
	}
	else
	{
		_asm {
			cmp ds : 0x6EC990, 4
			jmp jmpContinue
		}
	}
}

int CStuff::GetHunterAboutToBeExecuted()
{
	CEntity* plr = FindPlayer();
	CEntity* hunt = *(CEntity**)((int)plr + 0x1144);

	return (int)hunt;
}
