# RayTracing

Simple CPU ray tracer following the excellent [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview) book.

Generates a single .ppm image of the ray traced scene. Can use [this website](cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html) to view the output file.

![RayTracing](https://github.com/Narvin-Chana/RayTracingInAWeekend/assets/36044215/6fe82894-33b8-47b3-a8f6-635cfaedaf04)

## Installation

Requires Visual Studio 2022, with no other external libraries. 

Uses glm for math.

- Simply open the .sln and compile.
- The default scene can be tweaked in RayTracing.cpp.
- Then use the .exe in the following manner :
`RayTracing.exe >> myOutputFile.ppm`
