#include <iostream>
#include <chrono>

#include "Camera.h"
#include "Color.h"
#include "Scene.h"
#include "Sphere.h"

#include <glm/ext.hpp>

using namespace std::chrono;
using std::flush;
using glm::vec3;

int main()
{
	// Image
	const Camera camera;

	// World Scene
	const Scene scene{Sphere({0, 0, -1.0f}, 0.5f), Sphere({0, -100.5f, -1.0f}, 100)};

	const auto start = high_resolution_clock::now();
	camera.Render(scene);
	const auto end = high_resolution_clock::now();
	std::clog << "\rDone in " << duration_cast<milliseconds>(end - start) << "\r\n" << flush;
}
