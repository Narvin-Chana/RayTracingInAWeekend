#pragma once
#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(const float refractionIndex) : refractionIndex{ refractionIndex } {}

	bool Scatter(const Ray& in, const Hittable::HitRecord& record, Color& attenuation, Ray& scattered) const override;

private:
	float refractionIndex;

	static float SchlickReflectance(const float cos, const float refIdx)
	{
		float r0 = (1 - refIdx) / (1 + refIdx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * powf(1 - cos, 5);
	}
};
