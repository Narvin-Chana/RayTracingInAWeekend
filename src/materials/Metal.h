#pragma once
#include "Material.h"

class Metal : public Material
{
public:
	Metal(const Color& col, const float f) : albedo(col), fuzz{f < 1 ? f : 1}
	{
	}

	bool Scatter(const Ray& in, const Hittable::HitRecord& record, Color& attenuation, Ray& scattered) const override;

private:
	Color albedo;
	float fuzz;
};
