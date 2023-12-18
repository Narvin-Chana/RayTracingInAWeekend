#include <iostream>
#include <chrono>

#include <glm/ext.hpp>

#include "geometry/Scene.h"
#include "geometry/Sphere.h"
#include "Camera.h"
#include "Color.h"
#include "materials/Dielectric.h"
#include "materials/Lambertian.h"
#include "materials/Metal.h"

using namespace std::chrono;
using std::flush;
using glm::vec3;

int main()
{
	// Image
	const Camera camera;

	// World Scene
	const auto materialGround = std::make_unique<Lambertian>(Color(0.8, 0.8, 0.0));
	const auto materialCenter = std::make_unique<Lambertian>(Color(0.1, 0.2, 0.5));
	const auto materialLeft = std::make_unique<Dielectric>(1.5f);
	const auto materialRight = std::make_unique<Metal>(Color(0.8, 0.6, 0.2), 0.7f);

	const Scene scene{
		Sphere({0.0f, -100.5f, -1.0f}, 100, materialGround.get()),
		Sphere({0.0f, 0.0f, -1.0f}, 0.5f, materialCenter.get()),
		Sphere({-1.0f, 0.0f, -1.0f}, 0.5f, materialLeft.get()),
		Sphere({1.0f, 0.0f, -1.0f}, 0.5f, materialRight.get())
	};

	const auto start = high_resolution_clock::now();
	camera.Render(scene);
	const auto end = high_resolution_clock::now();
	std::clog << "\rDone in " << duration_cast<milliseconds>(end - start) << "\r\n" << flush;
}
