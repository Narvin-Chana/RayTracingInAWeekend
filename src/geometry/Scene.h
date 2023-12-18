#pragma once
#include <vector>

#include "Hittable.h"

class Scene : public Hittable
{
public:
	Scene() = default;

	template <class... Ts> requires (std::derived_from<Ts, Hittable> && ...)
	explicit Scene(Ts... ts)
	{
		std::unique_ptr<Hittable> objArr[] = {std::make_unique<Ts>(std::move(ts))...};
		objects = std::vector<std::unique_ptr<Hittable>>{
			std::make_move_iterator(std::begin(objArr)), std::make_move_iterator(std::end(objArr))
		};
	}

	~Scene() override = default;

	bool Hit(const Ray& ray, const Interval rayInterval, HitRecord& record) const override
	{
		HitRecord rec;
		bool hitAnything = false;
		float closestSoFar = rayInterval.max;

		for (const auto& object : objects)
		{
			if (object->Hit(ray, Interval(rayInterval.min, closestSoFar), rec))
			{
				hitAnything = true;
				closestSoFar = rec.t;
				record = rec;
			}
		}

		return hitAnything;
	}

	std::vector<std::unique_ptr<Hittable>> objects;
};
