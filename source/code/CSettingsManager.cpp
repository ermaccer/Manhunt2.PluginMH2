#include "CSettingsManager.h"
CSettingsManager* SettingsMgr = new CSettingsManager();

void CSettingsManager::Init()
{
	CIniReader reader("");


	bDisableLegalScreen = reader.ReadBoolean("Settings", "bDisableLegalScreen", false);
	bForceRatsToAppear = reader.ReadBoolean("Settings", "bForceRatsToAppear", false);
	bEnable60FPSPatch = reader.ReadBoolean("Settings", "bEnable60FPSPatch", false);
	bEnableCleanHeadshots = reader.ReadBoolean("Settings", "bEnableCleanHeadshots", false);
	bDisableCameraShake = reader.ReadBoolean("Settings", "bDisableCameraShake", false);
	bEnableAllExecutionLevelsForFirearms = reader.ReadBoolean("Settings", "bEnableAllExecutionLevelsForFirearms", false);
	bFixDisappearingDecals = reader.ReadBoolean("Settings", "bFixDisappearingDecals", false);
	bUseGlobalAnimationFiles = reader.ReadBoolean("Settings", "bUseGlobalAnimationFiles", false);

	iStreamingMemory = reader.ReadInteger("Settings", "iStreamingMemory", 0);


}
