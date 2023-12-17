#pragma once
#include <random>

struct Interval
{
	using ValueType = std::numeric_limits<float>;

	float min, max;

	Interval() : min{+ValueType::infinity()}, max{-ValueType::infinity()}
	{
	}

	Interval(const float min, const float max) : min{min}, max{max}
	{
	}

	bool Contains(const float x) const
	{
		return min <= x && x <= max;
	}

	bool Surrounds(const float x) const
	{
		return min < x && x < max;
	}
};

const static Interval Empty(+Interval::ValueType::infinity(), -Interval::ValueType::infinity());
const static Interval Universe(-Interval::ValueType::infinity(), +Interval::ValueType::infinity());
