// dllmain.cpp : Defines the entry point for the DLL application.
// standalone from PluginMH
#include "..\shared\stdafx.h"
#include "..\shared\IniReader.h"
#include "..\shared\MemoryMgr.h"
#include "common.h"

using namespace Memory::VP;
void GetFuncs()
{
	WriteDebug = (void(__cdecl *)(int,char*))0x53D8D0;
}

void GetIniValues()
{
	CIniReader reader("PluginMH2.ini");
	KeyMH2ShowCoordinates = reader.ReadInteger("Settings", "KeyMH2ShowCoordinates", 0x74);
	KeyMH2BaseScreenshotMode = reader.ReadInteger("Settings", "KeyMH2BaseScreenshotMode", 0x11);
	KeyMH2EnableScreenshotMode = reader.ReadInteger("Settings", "KeyMH2EnableScreenshotMode", 0x56);
	KeyMH2DisableScreenshotMode = reader.ReadInteger("Settings", "KeyMH2DisableScreenshotMode", 0x42);
	MH2ForceRatsToAppear = reader.ReadBoolean("Settings", "ForceRatsToAppear", 0);
	MH2NoLegalScreen = reader.ReadBoolean("Settings", "DisableLegalScreen", 0);
	MH2EnableScreenshotMode = reader.ReadBoolean("Settings", "EnableScreenshotMode", 0);
	MH2Enable60FPSPatch = reader.ReadBoolean("Settings", "Enable60FPSPatch", 0);
	MH2EnableGlobalAnimsIFP = reader.ReadBoolean("Settings", "EnableGlobalAnimsIFP ", 0);
	MH2FunMode= reader.ReadBoolean("Settings", "EnableFunMode", 0);
}

void WINAPI Init()
{
	GetFuncs();
	GetIniValues();
	Sleep(10);
		while (true) {
			if (KeyHit(KeyMH2ShowCoordinates)) DisplayPlayerCoords();
			// levels requires rat paths? they appear in good ending without this 
			// patch
			if (MH2ForceRatsToAppear) Patch(0x7942B4, 32);
			if (MH2Enable60FPSPatch) Patch(0x40D2A3, 0x412B);
			if (MH2EnableGlobalAnimsIFP) Patch<const char*>(0x662414, "../global/anims");

			// sor3nt findings
			if (MH2FunMode)
			{
				// replace models
				Patch<int>(0x76BE40, 32);
				// replace blood with flowers/sfx
				Patch<char>(0x6B26E5, 0);
			}

			if (MH2NoLegalScreen)
			{
				Patch(0x53FC68, 0);
				Patch(0x53FC50, 0);
				Patch(0x53FC6F, 0);
			}

			//TODO: Disable need for Disable/Enable key
			if (MH2EnableScreenshotMode)
			{
				if (KeyHit(KeyMH2BaseScreenshotMode) && KeyHit(KeyMH2EnableScreenshotMode))
				{
					
					FreeCamera = 1; DisableHudAndFreezeWorld = 1;
				}
				if (KeyHit(KeyMH2BaseScreenshotMode) && KeyHit(KeyMH2DisableScreenshotMode))
				{

					FreeCamera = 0; DisableHudAndFreezeWorld = 0;
				}
			}

			Sleep(1);
		}
}



BOOL WINAPI DllMain( HMODULE hModule, DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		if (*(int*)0x63BC93 != (unsigned int)'hnaM')
		{
			MessageBoxA(0, "Invalid executable!", 0, 0);
			return -1;
		}
		else CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);
	}
	return TRUE;
}

