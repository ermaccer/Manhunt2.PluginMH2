#pragma once

namespace CStuff {
	int   __fastcall  HookIsFirearm(int ptr);
	int   __fastcall  HookCheckExecutionWeaponType(int ptr);
	void HookSetMaxNumberOfRats();
	void HeapGeneration();

}