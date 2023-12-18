#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Hittable.h"
#include "materials/Material.h"
#include "Ray.h"

using glm::vec3;

struct Sphere : Hittable
{
	vec3 center{};
	float radius{};
	const Material* material;

	Sphere(const vec3 center, const float radius, const Material* material)
		: center{center}
		  , radius{radius}
		  , material{material}
	{
	}

	bool Hit(const Ray& ray, const Interval rayInterval, HitRecord& record) const override
	{
		const vec3 oc = ray.GetOrigin() - center;
		const float a = length2(ray.GetDirection());
		const float halfB = dot(oc, ray.GetDirection());
		const float c = length2(oc) - radius * radius;
		const float discriminant = halfB * halfB - a * c;

		if (discriminant < 0)
		{
			return false;
		}

		const float sqrtd = sqrtf(discriminant);

		// Find the nearest root in the [TMin,TMax] range
		float root = (-halfB - sqrtd) / a;
		if (!rayInterval.Surrounds(root))
		{
			root = (-halfB + sqrtd) / a;
			if (!rayInterval.Surrounds(root))
				return false;
		}

		record.t = root;
		record.point = ray.GetPoint(record.t);
		record.material = material;
		record.SetFaceNormal(ray, (record.point - center) / radius);

		return true;
	}
};
