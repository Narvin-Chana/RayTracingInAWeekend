#pragma once

#include <numbers>

inline float DegToRad(const float deg)
{
	return deg * std::numbers::pi_v<float> / 180.0f;
}