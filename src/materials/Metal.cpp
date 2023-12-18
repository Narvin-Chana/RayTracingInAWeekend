#include "Metal.h"

bool Metal::Scatter(const Ray& in, const Hittable::HitRecord& record, Color& attenuation, Ray& scattered) const
{
	const vec3 reflected = reflect(normalize(in.GetDirection()), record.normal);
    scattered = Ray(record.point, reflected + fuzz * RandomVec3Unit());
    attenuation = albedo;
    return dot(scattered.GetDirection(), record.normal) > 0;
}
