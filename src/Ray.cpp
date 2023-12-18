#include "Ray.h"

#include "geometry/Hittable.h"
#include "materials/Material.h"
#include "utils/MathUtil.h"

using namespace glm;

Color Ray::ToColor(const Hittable& worldObject, const int depth) const
{
	if (depth <= 0)
		return Color(0);

	if (Hittable::HitRecord hr; worldObject.Hit(*this, Interval(0.001f, Interval::ValueType::infinity()), hr))
	{
		Ray scattered;
		Color attenuation{};

		if (hr.material->Scatter(*this, hr, attenuation, scattered))
			return attenuation * scattered.ToColor(worldObject, depth - 1);
		return {};
	}

	const vec3 unitDir = normalize(direction);
	const float a = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - a) * Color(1.0f, 1.0f, 1.0f) + a * Color(0.5f, 0.7f, 1.0f);
}
