# CMakeList.txt : CMake project for Raytracer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Raytracer "Raytracer.cpp" "Raytracer.h" "Vector3.cpp" "Vector3.h" "Colour.h" "Ray.h" "Hittable.h" "Sphere.h" "HittableList.h" "MathConstants.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Raytracer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
