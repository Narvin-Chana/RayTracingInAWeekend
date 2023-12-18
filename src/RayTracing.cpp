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
	// World Scene
	const auto materialGround = std::make_unique<Lambertian>(Color(0.5, 0.5, 0.5));
	//const auto materialCenter = std::make_unique<Lambertian>(Color(0.1, 0.2, 0.5));
	//const auto materialLeft = std::make_unique<Dielectric>(1.5f);
	//const auto materialRight = std::make_unique<Metal>(Color(0.8, 0.6, 0.2), 0.7f);

	//const Scene scene{
	//	Sphere({0.0f, -100.5f, -1.0f}, 100, materialGround.get()),
	//	Sphere({0.0f, 0.0f, -1.0f}, 0.5f, materialCenter.get()),
	//	Sphere({-1.0f, 0.0f, -1.0f}, 0.5f, materialLeft.get()),
	//	Sphere({1.0f, 0.0f, -1.0f}, 0.5f, materialRight.get())
	//};

	Scene scene;

	std::vector<std::unique_ptr<Material>> materials;

	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			const float chooseMaterial = RandomFloat();
			vec3 center{a + 0.9f * RandomFloat(), 0.2f, b + 0.9f * RandomFloat()};

			if ((center - vec3(4, 0.2f, 0)).length() > 0.9f)
			{
				std::unique_ptr<Material> material;

				if (chooseMaterial < 0.8f)
				{
					// Diffuse
					vec3 albedo = RandomVec3(0, 1) * RandomVec3(0, 1);
					material = std::make_unique<Lambertian>(albedo);
					scene.objects.emplace_back(std::make_unique<Sphere>(center, 0.2f, material.get()));
				}
				else if (chooseMaterial < 0.95f)
				{
					// metal
					vec3 albedo = RandomVec3(0.5f, 1);
					float fuzz = RandomFloat();
					material = std::make_unique<Metal>(albedo, fuzz);
					scene.objects.emplace_back(std::make_unique<Sphere>(center, 0.2f, material.get()));
				}
				else
				{
					// glass
					material = std::make_unique<Dielectric>(1.5f);
					scene.objects.emplace_back(std::make_unique<Sphere>(center, 0.2f, material.get()));
				}

				materials.push_back(std::move(material));
			}
		}
	}

	const auto material1 = std::make_unique<Dielectric>(1.5f);
	scene.objects.push_back(std::make_unique<Sphere>(vec3(0, 1, 0), 1.0f, material1.get()));

	const auto material2 = std::make_unique<Lambertian>(vec3(0.4f, 0.2f, 0.1f));
	scene.objects.push_back(std::make_unique<Sphere>(vec3(-4, 1, 0), 1.0f, material2.get()));

	const auto material3 = std::make_unique<Metal>(vec3(0.7f, 0.6f, 0.5f), 0.0f);
	scene.objects.push_back(std::make_unique<Sphere>(vec3(4, 1, 0), 1.0f, material3.get()));

	// Image
	Camera camera;
	camera.aspectRatio = 16.0f / 9.0f;
	camera.imageWidth = 1200;
	camera.samplesPerPixel = 500;
	camera.maxDepth = 50;

	camera.vfov = 20;
	camera.lookfrom = vec3(13, 2, 3);
	camera.lookat = vec3(0, 0, 0);
	camera.vup = vec3(0, 1, 0);

	camera.dofAngle = 0.6f;
	camera.focusDistance = 10.0f;

	const auto start = high_resolution_clock::now();
	camera.Render(scene);
	const auto end = high_resolution_clock::now();
	std::clog << "\rDone in " << duration_cast<milliseconds>(end - start) << "\r\n" << flush;
}
