#include "Lambertian.h"

bool Lambertian::Scatter(const Ray& in, const Hittable::HitRecord& record, Color& attenuation, Ray& scattered) const
{
	vec3 scatterDirection = record.normal + RandomVec3Unit();

	// Avoid a degenerate scatter direction (normal and randVec being opposite would give almost null scatter direction)
	if (NearZero(scatterDirection))
		scatterDirection = record.normal;

	scattered = Ray(record.point, scatterDirection);
	attenuation = albedo;
	return true;
}
