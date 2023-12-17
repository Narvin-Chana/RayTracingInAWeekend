#include "Ray.h"

#include "Hittable.h"
#include "Sphere.h"

using namespace glm;

Color Ray::ToColor(const Hittable& worldObject) const
{
	if (Hittable::HitRecord hr; worldObject.Hit(*this, Interval(0, Interval::ValueType::infinity()), hr))
	{
		return 0.5f * (hr.normal + Color(1));
	}

	const vec3 unitDir = normalize(direction);
	const float a = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}
