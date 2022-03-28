#include "..\pch.h"
#include "CCleanHeadshots.h"
#include "mh2.h"
#include "..\MemoryMgr.h"
using namespace Memory::VP;


void __declspec(naked) CCleanHeadshots::HookExtraWeaponCheck()
{
	static int explodeHead_true = 0x5097FC;
	static int explodeHead_false = 0x5097C1;
	static int explodeHead_ebx;
	static int explodeHead_unk;

	_asm {
		mov explodeHead_ebx, ebx
		mov explodeHead_unk, eax
		pushad
	}

	if (explodeHead_ebx == CT_SAWNOFF || explodeHead_ebx == CT_SHOTGUN || explodeHead_ebx == CT_SHOTGUN_TORCH)
	{
		if (explodeHead_unk != *(char*)0x69939C)
		{
			Patch<float>(0x6991C0, 10.0);
			_asm
			{
				popad
				jmp explodeHead_true
			}
		}
	}
	else
	{
		Patch<float>(0x6991C0, 100.0);
		_asm {
			popad
			jmp  explodeHead_false
		}
	}
}
