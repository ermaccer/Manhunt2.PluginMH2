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

