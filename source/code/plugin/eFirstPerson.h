#pragma once

class eFirstPerson {
public:
	static bool m_bUnlockCamera;

	static void _null();
	static void Init();
	static void LookaroundUpdate();
	static void LookaroundHook();

	static void InputThread();
};