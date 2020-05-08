#include "CDecalsFix.h"

CVector4 * CDecalsFix::Vector3Add(CVector4 * vec, CVector4 * vec2, CVector4 * vec3)
{
	vec->x = vec2->x + vec3->x;
	vec->y = vec2->y + vec3->y;
	vec->z = vec2->z + vec3->z;
	vec->w = 1.0f;
	return vec;
}
