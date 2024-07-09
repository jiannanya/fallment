#pragma once
#ifndef AABB_H
#define AABB_H

#include "common/defines.h"
#include "math/vec3.h"
#include "glm/glm.hpp"

namespace hi{

class AABB{
    MAKE_PTR(AABB)

public:
    AABB() = default;
    AABB(Vec3f max, Vec3f min){_max = max; _min = min;}

    AABB operator+(const Vec3f&);
	AABB operator-(const Vec3f&);

    inline void expandBy(const Vec3f& v)
    {
        if(v.x<_min.x) _min.x = v.x;
        if(v.x>_max.x) _max.x = v.x;

        if(v.y<_min.y) _min.y = v.y;
        if(v.y>_max.y) _max.y = v.y;

        if(v.z<_min.z) _min.z = v.z;
        if(v.z>_max.z) _max.z = v.z;
    }

    inline void expandBy(const AABB& other_aabb)
    {
        if(other_aabb.xMin()<_min.x) _min.x = other_aabb.xMin();
        if(other_aabb.xMax()>_max.x) _max.x = other_aabb.xMax();

        if(other_aabb.yMin()<_min.y) _min.y = other_aabb.yMin();
        if(other_aabb.yMax()>_max.y) _max.y = other_aabb.yMax();

        if(other_aabb.zMin()<_min.z) _min.z = other_aabb.zMin();
        if(other_aabb.zMax()>_max.z) _max.z = other_aabb.zMax();
    }

    inline float& xMin() { return _min.x; }
    inline float xMin() const { return _min.x; }

    inline float& yMin() { return _min.y; }
    inline float yMin() const { return _min.y; }

    inline float& zMin() { return _min.z; }
    inline float zMin() const { return _min.z; }

    inline float& xMax() { return _max.x; }
    inline float xMax() const { return _max.x; }

    inline float& yMax() { return _max.y; }
    inline float yMax() const { return _max.y; }

    inline float& zMax() { return _max.z; }
    inline float zMax() const { return _max.z; }

    inline const Vec3f center() const
    {
        return (_min+_max)*0.5;
    }

private:

    Vec3f _max;
    Vec3f _min;


};

}

#endif