#include <iostream>
#include <chrono>

#include "Color.h"
#include "Ray.h"

using std::cout, std::clog, std::flush;
using namespace std::chrono;
using glm::vec3;

int main()
{
	// Image
	constexpr float aspectRatio = 16.0f / 9.0f;
	constexpr int imageWidth = 400;

	// Calculate the image height, and ensure that it's at least 1.
	int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	// Viewport widths less than one are ok since they are real valued.
	constexpr float focalLength = 1.0f;
	constexpr float viewportHeight = 2.0f;
	const float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / static_cast<float>(imageHeight));
	vec3 cameraCenter{};

	const vec3 viewportU = vec3{viewportWidth, 0, 0};
	constexpr vec3 viewportV = vec3{0, -viewportHeight, 0};

	auto pixelDeltaU = viewportU / static_cast<float>(imageWidth);
	auto pixelDeltaV = viewportV / static_cast<float>(imageHeight);

	auto viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewportU / 2.0f - viewportV / 2.0f;
	auto pixel00Location = viewportUpperLeft + 0.5f * (pixelDeltaU + pixelDeltaV);

	// Render
	cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	const auto start = high_resolution_clock::now();

	for (int j = 0; j < imageHeight; ++j)
	{
		clog << "\rScanlines remaining: " << imageHeight - j << " of " << imageHeight << ' ' << flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			vec3 pixelCenter = pixel00Location + static_cast<float>(i) * pixelDeltaU + static_cast<float>(j) * pixelDeltaV;
			vec3 rayDirection = pixelCenter - cameraCenter;

			Ray ray(cameraCenter, rayDirection);

			WriteColor(std::cout, ray.ToColor());
		}
	}
	const auto end = high_resolution_clock::now();

	std::clog << "\rDone in " << duration_cast<milliseconds>(end - start) << "\r\n" << flush;
}
