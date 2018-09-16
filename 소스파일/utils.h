#pragma once

#define PI 3.141592654f
#define PI2 PI * 2

namespace OCTA_UTIL
{
	//hypo 구하자
	float getDistance(float x1, float y1, float x2, float y2);

	//역각 구하자
	float getAngle(float x1, float y1, float x2, float y2);

}