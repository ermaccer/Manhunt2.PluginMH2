#pragma once
#include <iostream>


// plugin variables

int KeyMH2BaseScreenshotMode;
int KeyMH2EnableScreenshotMode;
int KeyMH2DisableScreenshotMode;
int KeyMH2ShowCoordinates;
bool MH2NoLegalScreen;
bool MH2ForceRatsToAppear;
bool MH2EnableScreenshotMode;
bool MH2Enable60FPSPatch;
bool MH2EnableGlobalAnimsIFP;
bool MH2FunMode;

// weird address, can glitch stuff
// TODO: find a better one 
int& DisableHudAndFreezeWorld = *(int*)0x78949C;
int& FreeCamera = *(int*)0x7894A4;

float& MH2PlayerX = *(float *)0x704F68;
float& MH2PlayerY = *(float *)0x704F70;
float& MH2PlayerZ = *(float *)0x704F6C;

// Functions
void(__cdecl *WriteDebug)(int, char*);

bool KeyHit(unsigned int keyCode) 
{
	return (GetKeyState(keyCode) & 0x8000) != 0;
}

void DisplayPlayerCoords()
{
	char buffer[64];
	sprintf_s(buffer, "X = %f Y = %f Z = %f", MH2PlayerX, MH2PlayerY, MH2PlayerZ);
	WriteDebug(10, buffer);
}

void MemPatch(void* address, void* data, int size)
{
	unsigned long flOld[2];
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &flOld[0]);
	memcpy(address, data, size);
	VirtualProtect(address, size, flOld[0], &flOld[1]);
}


void ReplaceCall(int address, void *func)
{
	int temp = 0xE8;
	MemPatch((void *)address, &temp, 1);
	temp = (int)func - ((int)address + 5);
	MemPatch((void *)((int)address + 1), &temp, 4);
}

void no_func() {}

void ReplaceJump(int address, void *func)
{
	int temp = 0xE9;
	MemPatch((void *)address, &temp, 1);
	temp = (int)func - ((int)address + 5);
	MemPatch((void *)((int)address + 1), &temp, 4);
}