#include "core.h"
#include "Ped.h"

void CPed::UpdateHeading()
{
	CallMethod<0x4F8050, CPed*>(this);
}

int CPed::GetBoneFrame(int frame)
{
	return CallMethodAndReturn<int,0x4F7E00, CPed*, int>(this, frame);
}

bool CPed::isCrawling()
{
	return CallMethodAndReturn<bool, 0x4F8DC0, CPed*>(this);
}
