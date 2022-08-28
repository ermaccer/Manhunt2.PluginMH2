// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "code/CSettingsManager.h"
#include "code/CStuff.h"
#include "code/CCleanHeadshots.h"
#include "code/CDecalsFix.h"
#include "code/plugin/eFirstPerson.h"
#include "code/plugin/eFOVAdjustment.h"
#include "MemoryMgr.h"


using namespace Memory::VP;

int GenericTrueReturn() { return 1; }
int GenericFalseReturn() { return 0; }
void  GenericDummy() { }


void Init()
{
	SettingsMgr->Init();
#ifdef _DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif // DEBUG


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
		Patch<char>(0x6596FC, 0x00);
	}

	if (SettingsMgr->bDisableCameraShake)
		Memory::VP::Patch<char>(0x5956CA + 1, 0x85);


	if (SettingsMgr->bFixDisappearingDecals)
	{
		InjectHook(0x5EE343, 0x57FF10);
		InjectHook(0x5EDE3B, CDecalsFix::Vector3Add);
	}

	if (SettingsMgr->bDisableExecutionCamera)
	{
		Nop(0x5B2630, 7);
		InjectHook(0x5B2630, CStuff::DisableExecutionCamera, PATCH_JUMP);
	}

	if (SettingsMgr->bFirstPersonMode)
	{
		eFirstPerson::Init();
		SettingsMgr->bDisableCloseupTransparency = true;
	}

	if (SettingsMgr->fFOVFactor > 0.0)
		eFOVAdjustment::Init();


	if (SettingsMgr->bDisableCloseupTransparency)
		InjectHook(0x592650, GenericDummy, PATCH_JUMP);

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