#pragma once

// Include(s)
#include <math.h>

// Radian-Degree Conversion Functions
#define rads(d) (d * M_PI / 180.0f)
#define degs(r) (r * 180.0f / M_PI)

// 1D Vector
typedef float vec1;

// 2D Vector
struct vec2 {
    // Data
    union {
        // Position
        struct {
            float x, y;
        };

        // Texture Coordinate
        struct {
            float u, v;
        };

        // Point
        float p[2];
    };

    // ---- Constructors

    // vec2(x, y) Constructor
    vec2(float x, float y);

    // vec2({x, y}) Constructor
    vec2(float xy[2]);

    // vec2(xy) Constructor
    vec2(float xy = 0.0f);

    // ---- Operator Overloading (vec2)

    // [+] Operator (vec2)
    vec2 operator+(const vec2 v) const;

    // [-] Operator (vec2)
    vec2 operator-(const vec2 v) const;

    // [*] Operator (vec2)
    vec2 operator*(const vec2 v) const;

    // [/] Operator (vec2)
    vec2 operator/(const vec2 v) const;

    // [+=] Operator (vec2)
    void operator+=(const vec2 v);

    // [-=] Operator (vec2)
    void operator-=(const vec2 v);

    // [*=] Operator (vec2)
    void operator*=(const vec2 v);

    // [/=] Operator (vec2)
    void operator/=(const vec2 v);

    // [=] Operator (vec2)
    void operator=(const vec2 v);

    // [==] Operator (vec2)
    bool operator==(const vec2 v) const;

    // [!=] Operator (vec2)
    bool operator!=(const vec2 v) const;

    // ---- Operator Overloading (float)

    // [+] Operator (float)
    vec2 operator+(const float v) const;
    // [-] Operator (float)
    vec2 operator-(const float v) const;

    // [*] Operator (float)
    vec2 operator*(const float v) const;

    // [/] Operator (float)
    vec2 operator/(const float v) const;

    // [+=] Operator (float)
    void operator+=(const float v);

    // [-=] Operator (float)
    void operator-=(const float v);

    // [*=] Operator (float)
    void operator*=(const float v);

    // [/=] Operator (float)
    void operator/=(const float v);

    // [=] Operator (float)
    void operator=(const float v);

    // [==] Operator (float)
    bool operator==(const float v) const;

    // [!=] Operator (float)
    bool operator!=(const float v) const;

    // ---- Indexing

    // vec2[id] Get Operator
    float operator[](int i) const;

    // vec2[id] Set Operator
    float &operator[](int i);

    // ---- Functions

    // Avarage
    // vec2 avg(unsigned int n, ...);

    // Dot Product
    float dot(vec2 v);

    // Cross Product
    vec2 cross(vec2 v);

    // Length
    float length();

    // Distance
    float distance(vec2 v);

    // Normalize
    vec2 normalize();

    // Get Data
    float *data();
};

// 3D Vector
struct vec3 {
    // Data
    union {
        // Position
        struct {
            float x, y, z;
        };

        // Color
        struct {
            float r, g, b;
        };

        // Point
        float p[3];
    };

    // ---- Constructors

    // vec3(x, y, z) Constructor
    vec3(float x, float y, float z = 0.0f);

    // vec3({x, y, z}) Constructor
    vec3(float xyz[3]);

    // vec3(xyz) Constructor
    vec3(float xyz = 0.0f);

    // ---- Operator Overloading (vec3)

    // [+] Operator (vec2)
    vec3 operator+(const vec3 v) const;

    // [-] Operator (vec3)
    vec3 operator-(const vec3 v) const;

    // [*] Operator (vec3)
    vec3 operator*(const vec3 v) const;

    // [/] Operator (vec3)
    vec3 operator/(const vec3 v) const;

    // [+=] Operator (vec3)
    void operator+=(const vec3 v);

    // [-=] Operator (vec3)
    void operator-=(const vec3 v);

    // [*=] Operator (vec3)
    void operator*=(const vec3 v);

    // [/=] Operator (vec3)
    void operator/=(const vec3 v);

    // [=] Operator (vec3)
    void operator=(const vec3 v);

    // [==] Operator (vec3)
    bool operator==(const vec3 v) const;

    // [!=] Operator (vec3)
    bool operator!=(const vec3 v) const;

    // ---- Operator Overloading (float)

    // [+] Operator (float)
    vec3 operator+(const float v) const;

    // [-] Operator (float)
    vec3 operator-(const float v) const;

    // [*] Operator (float)
    vec3 operator*(const float v) const;

    // [/] Operator (float)
    vec3 operator/(const float v) const;

    // [+=] Operator (float)
    void operator+=(const float v);

    // [-=] Operator (float)
    void operator-=(const float v);

    // [*=] Operator (float)
    void operator*=(const float v);

    // [/=] Operator (float)
    void operator/=(const float v);

    // [=] Operator (float)
    void operator=(const float v);

    // [==] Operator (float)
    bool operator==(const float v) const;

    // [!=] Operator (float)
    bool operator!=(const float v) const;

    // ---- Indexing

    // vec2[id] Get Operator
    float operator[](int i) const;

    // vec2[id] Set Operator
    float &operator[](int i);

    // ---- Functions

    // Avarage
    // vec3 avg(unsigned int n, ...);

    // Dot Product
    float dot(vec3 v);

    // Cross Product
    vec3 cross(vec3 v);

    // Length
    float length();

    // Distanced
    float distance(vec3 v);

    // Normalize
    vec3 normalize();

    // Get Data
    float *data();
};
