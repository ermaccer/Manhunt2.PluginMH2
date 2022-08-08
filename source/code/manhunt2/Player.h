#pragma once
#include "Ped.h"

class CPlayer : public CAutoPed {
public:
	int GetPlayerFlags();
	bool IsExecuting();
	bool IsExecuteHunterAvailable();

	void StartLookAround();

	// random

	int GetCurrentWeaponSlot();

};