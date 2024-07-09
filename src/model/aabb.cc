#include "aabb.h"
#include "math/vec3.h"

namespace hi{

AABB AABB::operator+(const Vec3f& vec)
{
	return AABB{ _max + vec, _min + vec };
}


AABB AABB::operator-(const Vec3f& vec)
{
	return AABB{ _max - vec, _min - vec };
}

}