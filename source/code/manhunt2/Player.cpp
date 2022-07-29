#include "core.h"
#include "Player.h"

int CPlayer::GetPlayerFlags()
{
	return *(int*)((int)this + 0x111C);
}

bool CPlayer::IsExecuting()
{
	return CallMethodAndReturn<bool, 0x5981B0, CPlayer*>(this);
}

bool CPlayer::IsExecuteHunterAvailable()
{
	int ptr = *(int*)((int)this + 0x1144);
	return ptr ? true : false;
}

int CPlayer::GetCurrentWeaponSlot()
{
	return *(int*)((int)this + 968);
}
