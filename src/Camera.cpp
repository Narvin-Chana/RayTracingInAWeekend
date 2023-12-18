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

	center = lookfrom;
	// Viewport widths less than one are ok since they are real valued.
	const float theta = DegToRad(vfov);
	const float h = tanf(theta / 2);
	const float viewportHeight = 2 * h * focusDistance;
	const float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / static_cast<float>(imageHeight));

	w = normalize(lookfrom - lookat);
	u = normalize(cross(vup, w));
	v = cross(w, u);

	const vec3 viewportU = viewportWidth * u;
	const vec3 viewportV = viewportHeight * -v;

	pixelDeltaU = viewportU / static_cast<float>(imageWidth);
	pixelDeltaV = viewportV / static_cast<float>(imageHeight);

	const vec3 viewportUpperLeft = center - focusDistance * w - viewportU / 2.0f - viewportV / 2.0f;
	pixel00Location = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);

	const float dofRadius = focusDistance * tanf(DegToRad(dofAngle / 2.0f));
	dofDiskU = u * dofRadius;
	dofDiskV = v * dofRadius;
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

	// Shoot ray from somewhere random in the dofDisk to add in a depth of field effect depending on focus distance
	const vec3 rayOrigin = (dofAngle <= 0) ? center : DofDiskSample();
	const vec3 rayDirection = pixelSample - rayOrigin;

	return {rayOrigin, rayDirection};
}

vec3 Camera::PixelSampleSquare() const
{
	const float px = -0.5f + RandomFloat();
	const float py = -0.5f + RandomFloat();
	return px * pixelDeltaU + py * pixelDeltaV;
}

vec3 Camera::DofDiskSample() const
{
	vec3 p = RandomVec3InUnitDisk();
	return center + p[0] * dofDiskU + p[1] * dofDiskV;
}
