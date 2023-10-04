#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>

// Header-only 3-dimensional vector class
class Vec3 {
public:
    // Components
    float x,y,z;

    // Construct a Vec3 {0, 0, 0}
    Vec3() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    }

    // Construct a Vec3 {x, x, x}
    Vec3(float x) {
        this->x = x;
        this->y = x;
        this->z = x;
    }

    // Construct a Vec3 {x, y, z}
    Vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Deconstructor
    ~Vec3() {}  // Good practice, not really necessary


    // Arithmetics

    // Addition
    Vec3 operator+(const Vec3& v) const {
        return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    // Subtraction
    Vec3 operator-(const Vec3& v) const {
        return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    // Multiplication
    Vec3 operator*(const Vec3& v) const {
        return Vec3(this->x * v.x, this->y * v.y, this->z * v.z);
    }

    // Scalar multiplication
    Vec3 operator*(float s) const {
        return Vec3(this->x * s, this->y * s, this->z * s);
    }

    // Division
    Vec3 operator/(const Vec3& v) const {
        return Vec3(this->x / v.x, this->y / v.y, this->z / v.z);
    }

    // Scalar division
    Vec3 operator/(float s) const {
        if (s == 0.0) return Vec3 { }; // Division by zero, return a zero vector
        return Vec3(this->x / s, this->y / s, this->z / s);
    }


    // Negation
    Vec3 operator-() const {
        return Vec3(-this->x, -this->y, -this->z);
    }

    // Dot product
    float dot(const Vec3& v) const {
        return this->x * v.x + this->y * v.y + this->z * v.z;
    }

    // Length
    float length() const {
        return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    // Normalization
    Vec3 normalize() const {
        float l = this->length();
        return Vec3(this->x / l, this->y / l, this->z / l);
    }

    // Cross product
    Vec3 cross(const Vec3& v) const {
        return Vec3(
            this->y * v.z - this->z * v.y,
            this->z * v.x - this->x * v.z,
            this->x * v.y - this->y * v.x
        );
    }

    // Reflection
    Vec3 reflect(const Vec3& normal) const {
        return *this - normal * 2.0f * this->dot(normal);
    }

    // Absolute
    Vec3 abs() const {
        return Vec3(fabsf(this->x), fabsf(this->y), fabsf(this->z));
    }

    // Clamp
    Vec3 clamp(const Vec3& min, const Vec3& max) const {
        return Vec3(
            fmaxf(min.x, fminf(max.x, this->x)),
            fmaxf(min.y, fminf(max.y, this->y)),
            fmaxf(min.z, fminf(max.z, this->z))
        );
    }

    // Scalar clamp
    Vec3 clamp(float min, float max) const {
        return Vec3(
            fmaxf(min, fminf(max, this->x)),
            fmaxf(min, fminf(max, this->y)),
            fmaxf(min, fminf(max, this->z))
        );
    }

    // Linear interpolation
    static Vec3 mix(Vec3 a, Vec3 b, float t) {
        return a + (b - a) * t;
    }
};

#endif