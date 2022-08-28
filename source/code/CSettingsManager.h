#pragma once

#include "..\IniReader.h"

class CSettingsManager {
public:
	void Init();

	// vars
	bool bDisableLegalScreen;
	bool bForceRatsToAppear;
	bool bEnable60FPSPatch;
	bool bEnableCleanHeadshots;
	bool bDisableCameraShake;
	bool bEnableAllExecutionLevelsForFirearms;
	bool bFixDisappearingDecals;
	bool bUseGlobalAnimationFiles;
	bool bDisableExecutionCamera;
	bool bDisableCloseupTransparency;

	bool bFirstPersonMode;
	bool bFirstPersonAutoResetCamera;

	int  iStreamingMemory;
	int  iFirstPersonCameraUnlockKey;

	float fFOVFactor;
};

extern CSettingsManager* SettingsMgr;