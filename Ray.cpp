#include "Ray.h"

#include "Hittable.h"
#include "MathUtil.h"
#include "Sphere.h"

using namespace glm;

Color Ray::ToColor(const Hittable& worldObject, const int depth) const
{
	if (depth <= 0)
		return Color(0);

	if (Hittable::HitRecord hr; worldObject.Hit(*this, Interval(0, Interval::ValueType::infinity()), hr))
	{
		const vec3 randDirection = RandomOnHemisphere(hr.normal);
		return 0.5 * Ray(hr.point, randDirection).ToColor(worldObject, depth - 1);
	}

	const vec3 unitDir = normalize(direction);
	const float a = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}
