#pragma once
#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Color& col) : albedo(col)
	{
	}

	bool Scatter(const Ray& in, const Hittable::HitRecord& record, Color& attenuation, Ray& scattered) const override;

private:
	Color albedo;
};
