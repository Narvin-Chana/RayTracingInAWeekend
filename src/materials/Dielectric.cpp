#include "Dielectric.h"

bool Dielectric::Scatter(const Ray& in, const Hittable::HitRecord& record, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1);
	const float refractionRatio = record.isFrontFace ? (1.0f / refractionIndex) : refractionIndex;

	const vec3 unitDirection = normalize(in.GetDirection());

	const float cosTheta = fmin(dot(-unitDirection, record.normal), 1.0f);
	const float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);

	const bool cannotRefract = refractionRatio * sinTheta > 1.0f;

	vec3 direction;

	if (cannotRefract || SchlickReflectance(cosTheta, refractionRatio) > RandomFloat())
	{
		direction = reflect(unitDirection, record.normal);
	}
	else
	{
		direction = refract(unitDirection, record.normal, refractionRatio);
	}
	scattered = Ray(record.point, direction);
	return true;
}
