#pragma once
#include <glm/glm.hpp>

#include "Color.h"

class Ray
{
public:
	Ray() = default;

	Ray(const glm::vec3& origin, const glm::vec3& direction)
		: origin{origin},
		  direction{direction}
	{
	}

	[[nodiscard]] glm::vec3 GetOrigin() const noexcept { return origin; }
	[[nodiscard]] glm::vec3 GetDirection() const noexcept { return direction; }

	[[nodiscard]] glm::vec3 GetPoint(const float t) const noexcept
	{
		return origin + t * direction;
	}

	[[nodiscard]] Color ToColor() const;

private:
	glm::vec3 origin;
	glm::vec3 direction;
};
