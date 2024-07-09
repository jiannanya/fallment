#pragma once
#ifndef VEC3_H
#define VEC3_H

namespace hi
{
    



template<typename T>
struct Vec3 {

    T x, y, z;
    T r, g, b;
    T nx, ny, nz;
    T tx, ty;
    T tanx, tany, tanz;
    T bitanx, bitany, bitanz;

    bool hasTangents;

    Vec3(T _x, T _y, T _z, float _r = 1, float _g = 1, float _b = 1)
        : x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), nx(0), ny(0), nz(0), 
        tx(0), ty(0), tanx(0), tany(0), tanz(0), bitanx(0), bitany(0), bitanz(0),
        hasTangents(false) {
    }

    Vec3(T _x, T _y, T _z, float _r, float _g, float _b, T _nx, T _ny, T _nz)
        : x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), nx(_nx), ny(_ny), nz(_nz), tx(0), ty(0),
        tanx(0), tany(0), tanz(0), bitanx(0), bitany(0), bitanz(0), hasTangents(false) {
    }

    Vec3(T _x, T _y, T _z, float _r, float _g, float _b, T _nx, T _ny, T _nz, T _tx, T _ty)
        : x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), nx(_nx), ny(_ny), nz(_nz), tx(_tx), ty(_ty), 
        tanx(0), tany(0), tanz(0), bitanx(0), bitany(0), bitanz(0), hasTangents(false) {
    }

    Vec3() 
        : x(0), y(0), z(0), r(1), g(1), b(1), nx(0), ny(0), 
        nz(0), tx(0), ty(0), hasTangents(false) {
    }

    ~Vec3() = default;

    inline double getModule() { return sqrt(x * x + y * y + z * z); }

    inline double operator * (const Vec3& vec) { return vec.x * x + vec.y * y + vec.z * z; }
    inline const Vec3 operator * (const double d) const { return Vec3(x * d, y * d, z * d); }
    inline Vec3 operator ^ (const Vec3& vec) { return Vec3(y * vec.z - z * vec.y, -x * vec.z + z * vec.x, x * vec.y - y * vec.x); }
    inline Vec3 operator + (const Vec3& vec) { return Vec3(vec.x + x, vec.y + y, vec.z + z); }
    inline const Vec3 operator + (const Vec3& vec) const {return Vec3(vec.x + x, vec.y + y, vec.z + z);}
    inline Vec3 operator - (const Vec3& vec) { return Vec3(vec.x - x, vec.y - y, vec.z - z); }

    Vec3& operator * (T value) {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Vec3 getUnit() {
        double norm = getModule();
        return Vec3(x / norm, y / norm, z / norm);
    }
};

using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3i = Vec3<int>;


} // namespace hi

#endif