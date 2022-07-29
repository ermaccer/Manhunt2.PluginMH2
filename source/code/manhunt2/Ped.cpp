#include "core.h"
#include "Ped.h"

void CPed::UpdateHeading()
{
	CallMethod<0x4F8050, CPed*>(this);
}
