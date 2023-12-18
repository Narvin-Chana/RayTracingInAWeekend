#pragma once

#include <numbers>
#include <random>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;

static inline std::uniform_real_distribution distribution(0.0f, 1.0f);
static inline std::mt19937 generator(12345); // This is obviously bad

inline float DegToRad(const float deg)
{
	return deg * std::numbers::pi_v<float> / 180.0f;
}

inline float RandomFloat()
{
	return distribution(generator);
}

inline float RandomFloat(const float min, const float max)
{
	return min + (max - min) * RandomFloat();
}

inline vec3 RandomVec3()
{
	return {RandomFloat(), RandomFloat(), RandomFloat()};
}

inline vec3 RandomVec3(const float min, const float max)
{
	return {RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max)};
}

inline vec3 RandomVec3InUnitSphere()
{
	while (true)
	{
		if (vec3 sampleVec = RandomVec3(-1.0f, 1.0f); length2(sampleVec) < 1)
			return sampleVec;
	}
}

inline vec3 RandomVec3Unit()
{
	return normalize(RandomVec3InUnitSphere());
}

inline vec3 RandomOnHemisphere(const vec3& normal)
{
	const vec3 vec = RandomVec3Unit();
	return vec * ((dot(vec, normal) > 0.0f) * 2 - 1);
}

inline float LinearToGamma(const float linearComponent)
{
	return sqrtf(linearComponent);
}

inline bool NearZero(const vec3& v)
{
	// Return true if the vector is close to zero in all dimensions.
	constexpr float s = std::numeric_limits<float>::epsilon();
	return fabs(v.x) < s && fabs(v.y) < s && fabs(v.z) < s;
}
