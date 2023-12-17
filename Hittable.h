#pragma once

#include <glm/vec3.hpp>

#include "Interval.h"
#include "Ray.h"

using glm::vec3;

struct Hittable
{
	struct HitRecord
	{
		vec3 point;
		vec3 normal;
		float t;
		bool isFrontFace;

		void SetFaceNormal(const Ray& ray, const vec3& outwardNormal)
		{
			isFrontFace = dot(ray.GetDirection(), outwardNormal) < 0;
			normal = isFrontFace ? outwardNormal : -outwardNormal;
		}
	};

	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, Interval rayInterval, HitRecord& record) const = 0;
};
