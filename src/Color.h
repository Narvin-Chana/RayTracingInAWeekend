#pragma once

#include <ostream>

#include <glm/glm.hpp>

#include "Interval.h"
#include "utils/MathUtil.h"

using Color = glm::vec3;

inline void WriteColor(std::ostream& out, const Color pixelColor, const int samples)
{
	float r = pixelColor.x;
	float g = pixelColor.y;
	float b = pixelColor.z;

	// Divide the color by the number of samples.
	const float scale = 1.0f / static_cast<float>(samples);
	r *= scale;
	g *= scale;
	b *= scale;

	r = LinearToGamma(r);
	g = LinearToGamma(g);
	b = LinearToGamma(b);

	// Write the translated [0,255] value of each color component.
	const Interval intensity{0.000f, 0.999f};
	out << 256 * intensity.Clamp(r) << ' '
		<< 256 * intensity.Clamp(g) << ' '
		<< 256 * intensity.Clamp(b) << '\n';
}
