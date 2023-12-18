#include "Camera.h"

#include <iostream>

#include "Color.h"
#include "utils/MathUtil.h"
#include "Ray.h"
#include "geometry/Hittable.h"

using std::cout, std::clog, std::flush;

Camera::Camera()
	: center{}
{
	imageHeight = static_cast<int>(imageWidth / aspectRatio);
	imageHeight = imageHeight < 1 ? 1 : imageHeight;

	// Viewport widths less than one are ok since they are real valued.
	constexpr float focalLength = 1.0f;
	constexpr float viewportHeight = 2.0f;
	const float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / static_cast<float>(imageHeight));
	vec3 cameraCenter{};

	const vec3 viewportU = vec3{viewportWidth, 0, 0};
	constexpr vec3 viewportV = vec3{0, -viewportHeight, 0};

	pixelDeltaU = viewportU / static_cast<float>(imageWidth);
	pixelDeltaV = viewportV / static_cast<float>(imageHeight);

	auto viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewportU / 2.0f - viewportV / 2.0f;
	pixel00Location = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);
}

void Camera::Render(const Hittable& world) const
{
	cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = 0; j < imageHeight; ++j)
	{
		clog << "\rScanlines remaining: " << imageHeight - j << " of " << imageHeight << ' ' << flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			Color pixelColor{};

			for (int sample = 0; sample < samplesPerPixel; ++sample)
			{
				Ray r = GetRayFromLoc(i, j);
				pixelColor += r.ToColor(world, maxDepth);
			}

			WriteColor(std::cout, pixelColor, samplesPerPixel);
		}
	}
}

Ray Camera::GetRayFromLoc(const int i, const int j) const noexcept
{
	// Get a randomly sampled camera ray for the pixel at location i,j.
	const vec3 pixelCenter = pixel00Location + static_cast<float>(i) * pixelDeltaU + static_cast<float>(j) *
		pixelDeltaV;
	const vec3 pixelSample = pixelCenter + PixelSampleSquare();

	const vec3 rayOrigin = center;
	const vec3 rayDirection = pixelSample - rayOrigin;

	return {rayOrigin, rayDirection};
}

vec3 Camera::PixelSampleSquare() const
{
	const float px = -0.5f + RandomFloat();
	const float py = -0.5f + RandomFloat();
	return px * pixelDeltaU + py * pixelDeltaV;
}
