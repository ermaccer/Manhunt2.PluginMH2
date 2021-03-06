// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "code/CSettingsManager.h"
#include "code/CStuff.h"
#include "code/CCleanHeadshots.h"
#include "code/CDecalsFix.h"
#include "MemoryMgr.h"


using namespace Memory::VP;

void NullFunc() {}

void Init()
{
	SettingsMgr->Init();

	CStuff::HeapGeneration();

	if (SettingsMgr->bForceRatsToAppear)
	{
		Patch<int>(0x7942B4, 32);
		InjectHook(0x5EE9D0, CStuff::HookSetMaxNumberOfRats, PATCH_JUMP);
	}


	if (SettingsMgr->bEnable60FPSPatch)
		Patch<short>(0x40D2A3, 0x412B);

	if (SettingsMgr->bEnableAllExecutionLevelsForFirearms)
		InjectHook(0x599879, CStuff::HookIsFirearm, PATCH_CALL);

	if (SettingsMgr->bEnableCleanHeadshots)
		InjectHook(0x5097F1, CCleanHeadshots::HookExtraWeaponCheck, PATCH_JUMP);

	if (SettingsMgr->bDisableLegalScreen)
	{
		Patch<int>(0x53FC68, 0);
		Patch<int>(0x53FC50, 0);
		Patch<int>(0x53FC6F, 0);
	}

	if (SettingsMgr->bDisableCameraShake)
		Memory::VP::Patch<char>(0x5956CA + 1, 0x85);


	if (SettingsMgr->bFixDisappearingDecals)
	{
		InjectHook(0x5EE343, 0x57FF10);
		InjectHook(0x5EDE3B, CDecalsFix::Vector3Add);
	}


}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		if (*(int*)0x63BC93 != 'hnaM')
		{
			MessageBoxA(0, "Invalid executable!", "PluginMH2", 0);
		}
		else Init();
	}
}