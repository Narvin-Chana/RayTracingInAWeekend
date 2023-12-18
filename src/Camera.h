#pragma once
#include <glm/glm.hpp>

#include "Ray.h"

using glm::vec3;

struct Hittable;

class Camera
{
public:
	Camera();

	static constexpr float aspectRatio = 16.0f / 9.0f;
	static constexpr int imageWidth = 400;
	static constexpr int samplesPerPixel = 100; // Number of rays to shoot per pixel
	static constexpr int maxDepth = 50; // Number of max bounces

	int imageHeight;
	vec3 center;
	vec3 pixel00Location;
	vec3 pixelDeltaU;
	vec3 pixelDeltaV;

	void Render(const Hittable& world) const;
private:
	Ray GetRayFromLoc(int i, int j) const noexcept;
	vec3 PixelSampleSquare() const;
};
