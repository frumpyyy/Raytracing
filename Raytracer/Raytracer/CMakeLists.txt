# CMakeList.txt : CMake project for Raytracer

add_executable(Raytracer
    "Raytracer.cpp" "Raytracer.h"
    "Vector3.cpp"   "Vector3.h"
    "Colour.h"
    "Ray.h"
    "Hittable.h"
    "Sphere.h"
    "HittableList.h"
    "MathConstants.h"
    "Interval.h"
    "Camera.h"
    "Material.h"
)

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Raytracer PROPERTY CXX_STANDARD 20)
endif()

# ----- Release optimisation flags -------------------------------------------
# Always build with -O3 (or /O2 on MSVC) for a raytracer; the difference vs
# the default Debug build is typically 5–10×.
target_compile_options(Raytracer PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/O2 /fp:fast>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O3 -ffast-math -march=native>
)

# ----- OpenMP — parallelises the scanline loop ------------------------------
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Raytracer OpenMP::OpenMP_CXX)
    message(STATUS "OpenMP found — parallel rendering enabled")
else()
    message(WARNING "OpenMP not found — rendering will be single-threaded")
endif()