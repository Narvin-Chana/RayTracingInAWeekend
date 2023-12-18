#pragma once
#include "geometry/Hittable.h"
#include "Ray.h"

struct Material
{
	virtual ~Material() = default;
	virtual bool Scatter(const Ray& in, const Hittable::HitRecord& record, Color& attenuation,
	                     Ray& scattered) const = 0;
};
