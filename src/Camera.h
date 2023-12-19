#pragma once
#include <glm/glm.hpp>

#include "Ray.h"

using glm::vec3;

struct Hittable;

class Camera
{
public:

	float aspectRatio = 16.0f / 9.0f;
	int imageWidth = 400;
	int samplesPerPixel = 100; // Number of rays to shoot per pixel
	int maxDepth = 50; // Number of max bounces

	float vfov = 20; // Vertical view angle (field of view)
	vec3 lookfrom = vec3(-2, 2, 1); // Point camera is looking from
	vec3 lookat = vec3(0, 0, -1); // Point camera is looking at
	vec3 vup = vec3(0, 1, 0); // Camera-relative "up" direction

	float dofAngle = 10.0f; // Variation angle of rays through each pixel
	// Distance from camera lookfrom point to plane of perfect focus (imagine how your eyes focus on a specific point in the world)
	float focusDistance = 3.4f;

	void Init();
	void Render(const Hittable& world) const;

private:
	int imageHeight;
	vec3 center;
	vec3 pixel00Location;
	vec3 pixelDeltaU;
	vec3 pixelDeltaV;
	vec3 u, v, w; // Camera frame basis vectors
	vec3 dofDiskU; // Defocus disk horizontal radius
	vec3 dofDiskV; // Defocus disk vertical radius

	Ray GetRayFromLoc(int i, int j) const noexcept;
	vec3 PixelSampleSquare() const;
	vec3 DofDiskSample() const;
};
