#include "mh2.h"
char tempBuffer[256];

CEntity * GetEntity(const char * name)
{
	return CallAndReturn<CEntity*, 0x4E9130, const char*>(name);
}

void CreateInventoryItem(CEntity * ent, int item, bool b1)
{
	CallMethod<0x4F6500, CEntity*, int, bool>(ent, item, b1);
}

void AddAmmoToInventoryWeapon(int item, int amount)
{
	// using direct player pointer, not any entity
	// as spawner gives stuff to player anwyay
	int v0 = *(int*)(*(int*)0x789490 + 444);
	int v1 = ((int(__thiscall*)(int, int))0x5726F0)(v0, item);

	((void(__thiscall*)(int, int))0x5D2B30)(*(int*)(v1 + 516), amount);
}

void SetHunterHideHealth(CEntity * ent, float health)
{
	CallMethod<0x4E1D20, CEntity*, float>(ent, health);
}

CVector GetEntityPosition(CEntity * ent)
{
	return CVector();
}

CEntity* FindPlayer()
{
	return *(CEntity**)0x789490;
}

// script space only
CEntity * FindEntity(const char * name)
{
	return CallAndReturn<CEntity*, 0x4EC530, const char*>(name);
}

bool IsAlive(CEntity * ent)
{
	if (ent->health > 0.0)
		return true;
	else
		return false;
}

void SetDrawRGBA(int r, int g, int b, int a)
{
	Call<0x53F490, int, int, int, int>(r,g,b,a);
}

void PrintText(const char * text, float x, float y, float sizex, float sizey,float unk, EFontType font)
{
	Call<0x5443A0, const char*, float, float,float,float,float,EFontType>(text,x,y,sizex,sizey,unk,font);
}

void SetEntityFlag(CEntity * ent, int flag, bool state)
{
	CallMethod<0x41D3A0, CEntity*, int, bool>(ent, flag, state);
}

wchar_t * GetCollectableName(int id)
{
	return CallAndReturn<wchar_t*, 0x5248D0, int>(id);
}

char * GetRecordName(int id)
{
	Call<0x525D60, int, char*>(id, tempBuffer);
	return tempBuffer;
}

int GetTimer()
{
	return *(int*)0x6ECE6C;
}



// variables

int &Game::FreezeWorld = *reinterpret_cast<int *>(0x78949C);
int &Game::FreeCamera = *reinterpret_cast<int *>(0x7894A4);


int &Game::iHuntersExecuted = *reinterpret_cast<int *>(0x77B4B4);
int &Game::iHuntersKilled = *reinterpret_cast<int *>(0x77B444);
int &Game::iBodyCounterKills = *reinterpret_cast<int *>(0x75B738);

int &Game::iTimePassed = *reinterpret_cast<int *>(0x75CD14);
int &Game::iTimerMinutes =  *reinterpret_cast<int *>(0x75B72C);
int &Game::iTimerSeconds = *reinterpret_cast<int *>(0x75B730);
