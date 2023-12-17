#pragma once

#include <ostream>

#include <glm/glm.hpp>

using Color = glm::vec3;

inline void WriteColor(std::ostream& out, const Color pixelColor)
{
    out << static_cast<int>(255.999f * pixelColor.x) << ' '
        << static_cast<int>(255.999f * pixelColor.y) << ' '
        << static_cast<int>(255.999f * pixelColor.z) << '\n';
}