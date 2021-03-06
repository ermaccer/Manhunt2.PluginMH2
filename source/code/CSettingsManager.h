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

	int  iStreamingMemory;
};

extern CSettingsManager* SettingsMgr;