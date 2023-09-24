#pragma once

#include <cmath>
#include <cstdarg>
#include <cstdint>
#include <vector>

// Vector Components
namespace internal {
template <uint8_t D, typename T> struct vecC;
} // namespace internal

// Variable Dimension Vector
template <uint8_t D = 3, typename T = float> struct vec {
    static_assert(D != 0, "Null-Vectors are not supported");

    union {
        T data[D];

        internal::vecC<D, T> component;
    };

    // Constructors & Destructor

    vec(std::vector<T> v);
    template <typename... Args> vec(Args... args);
    template <uint8_t inD, typename inT> vec(vec<inD, inT> v);

    ~vec();

    // Arithmetic Operators

    template <uint8_t inD, typename inT>
    vec<D, T> operator+(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    vec<D, T> operator-(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    vec<D, T> operator*(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    vec<D, T> operator/(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    vec<D, T> operator%(const vec<inD, inT> &v) const;

    vec<D, T> operator*(const T &v) const;
    vec<D, T> operator/(const T &v) const;
    vec<D, T> operator%(const T &v) const;

    // Assignment Operators

    template <uint8_t inD, typename inT> void operator=(const vec<inD, inT> &v);
    template <uint8_t inD, typename inT>
    void operator+=(const vec<inD, inT> &v);
    template <uint8_t inD, typename inT>
    void operator-=(const vec<inD, inT> &v);
    template <uint8_t inD, typename inT>
    void operator*=(const vec<inD, inT> &v);
    template <uint8_t inD, typename inT>
    void operator/=(const vec<inD, inT> &v);
    template <uint8_t inD, typename inT>
    void operator%=(const vec<inD, inT> &v);

    void operator=(const T &v);
    void operator*=(const T &v);
    void operator/=(const T &v);
    void operator%=(const T &v);

    // Relational Operators

    template <uint8_t inD, typename inT>
    bool operator==(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    bool operator!=(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    bool operator>(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    bool operator<(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    bool operator>=(const vec<inD, inT> &v) const;
    template <uint8_t inD, typename inT>
    bool operator<=(const vec<inD, inT> &v) const;

    // Other Operators

    T operator[](uint8_t i) const;
    T &operator[](uint8_t i);

    void operator++();
    void operator--();

    internal::vecC<D, T> *operator->() { return &component; }
    const internal::vecC<D, T> *operator->() const { return &component; }

    // Functions (Instance Methods)

    T length() const;
    vec normalize() const;
    vec clamp(vec min, vec max) const;

    // Functions (Static)

    static T distance(vec a, vec b);
    static T dot(vec a, vec b);
    static vec lerp(vec a, vec b, T blend);

    // Functions (Dimension-Specific)

    static vec<3> cross(vec<3> a, vec<3> b);
};

// Simple Vectors (usually same as fvec)
typedef vec<1> vec1;
typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

// Floating-Point Vectors
typedef vec<1, float> fvec1;
typedef vec<2, float> fvec2;
typedef vec<3, float> fvec3;
typedef vec<4, float> fvec4;

// Double-Precision Vectors
typedef vec<1, double> dvec1;
typedef vec<2, double> dvec2;
typedef vec<3, double> dvec3;
typedef vec<4, double> dvec4;

// Integer Vectors
typedef vec<1, int> ivec1;
typedef vec<2, int> ivec2;
typedef vec<3, int> ivec3;
typedef vec<4, int> ivec4;

// Euler Angles
typedef vec<3> Euler;
typedef vec<3, float> fEuler;
typedef vec<3, double> dEuler;
typedef vec<3, int> iEuler;

namespace internal {

// 1D Vector Component
template <typename T> struct vecC<1, T> {
    T x;
};

// 2D Vector Components
template <typename T> struct vecC<2, T> {
    union {
        // Position
        struct {
            T x, y;
        };

        // TexCoord
        struct {
            T u, v;
        };

        // Width & Height
        struct {
            T w, h;
        };
    };
};

// 3D Vector Components
template <typename T> struct vecC<3, T> {
    union {
        // Position
        struct {
            T x, y, z;
        };

        // Color
        struct {
            T r, g, b;
        };

        // TexCoord
        struct {
            T u, v, w;
        };
    };
};

// 4D Vector Components
template <typename T> struct vecC<4, T> {
    union {
        // Position
        struct {
            T x, y, z, w;
        };

        // Color
        struct {
            T r, g, b, a;
        };
    };
};

} // namespace internal

// Constructors & Destructor

template <uint8_t D, typename T> vec<D, T>::vec(std::vector<T> v) {
    for (int i = 0; i < D; i++)
        this->data[i] = i < v.size() ? v[i] : 0;
}

template <uint8_t D, typename T>
template <typename... Args>
vec<D, T>::vec(Args... args) {
    T values[] = {static_cast<T>(args)...};
    for (uint8_t i = 0; i < D; i++)
        this->data[i] = sizeof...(args) == 1
                            ? values[0]
                            : (i < sizeof...(args) ? values[i] : 0);
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
vec<D, T>::vec(vec<inD, inT> v) {
    *this = v;
}

template <uint8_t D, typename T> vec<D, T>::~vec() {}

// Arithmetic Operators

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
vec<D, T> vec<D, T>::operator+(const vec<inD, inT> &v) const {
    vec<D, T> ret;
    for (uint8_t i = 0; i < std::min(D, inD); i++)
        ret.data[i] = this->data[i] + v.data[i];
    return ret;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
vec<D, T> vec<D, T>::operator-(const vec<inD, inT> &v) const {
    vec<D, T> ret;
    for (uint8_t i = 0; i < std::min(D, inD); i++)
        ret.data[i] = this->data[i] - v.data[i];
    return ret;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
vec<D, T> vec<D, T>::operator*(const vec<inD, inT> &v) const {
    vec<D, T> ret;
    for (uint8_t i = 0; i < std::min(D, inD); i++)
        ret.data[i] = this->data[i] * v.data[i];
    return ret;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
vec<D, T> vec<D, T>::operator/(const vec<inD, inT> &v) const {
    vec<D, T> ret;
    for (uint8_t i = 0; i < std::min(D, inD); i++)
        ret.data[i] = this->data[i] / v.data[i];
    return ret;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
vec<D, T> vec<D, T>::operator%(const vec<inD, inT> &v) const {
    vec<D, T> ret;
    for (uint8_t i = 0; i < std::min(D, inD); i++)
        ret.data[i] = this->data[i] % v.data[i];
    return ret;
}

template <uint8_t D, typename T>
vec<D, T> vec<D, T>::operator*(const T &v) const {
    vec<D, T> out;
    for (uint8_t i = 0; i < D; i++)
        out.data[i] = this->data[i] * v;
    return out;
}

template <uint8_t D, typename T>
vec<D, T> vec<D, T>::operator/(const T &v) const {
    vec<D, T> out;
    for (uint8_t i = 0; i < D; i++)
        out.data[i] = this->data[i] / v;
    return out;
}

template <uint8_t D, typename T>
vec<D, T> vec<D, T>::operator%(const T &v) const {
    vec<D, T> out;
    for (uint8_t i = 0; i < D; i++)
        out.data[i] = this->data[i] % v;
    return out;
}

// Assignment Operators

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
void vec<D, T>::operator=(const vec<inD, inT> &v) {
    for (uint8_t i = 0; i < D; i++)
        this->data[i] = i < inD ? v.data[i] : 0;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
void vec<D, T>::operator+=(const vec<inD, inT> &v) {
    *this = *this + v;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
void vec<D, T>::operator-=(const vec<inD, inT> &v) {
    *this = *this - v;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
void vec<D, T>::operator*=(const vec<inD, inT> &v) {
    *this = *this * v;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
void vec<D, T>::operator/=(const vec<inD, inT> &v) {
    *this = *this / v;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
void vec<D, T>::operator%=(const vec<inD, inT> &v) {
    *this = *this % v;
}

template <uint8_t D, typename T> void vec<D, T>::operator=(const T &v) {
    for (uint8_t i = 0; i < D; i++)
        this->data[i] = v;
}

template <uint8_t D, typename T> void vec<D, T>::operator*=(const T &v) {
    *this = *this * v;
}

template <uint8_t D, typename T> void vec<D, T>::operator/=(const T &v) {
    *this = *this / v;
}

template <uint8_t D, typename T> void vec<D, T>::operator%=(const T &v) {
    *this = *this % v;
}

// Relational Operators

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
bool vec<D, T>::operator==(const vec<inD, inT> &v) const {
    for (uint8_t i = 0; i < D; i++)
        if (this->data[i] != v.data[i])
            return false;
    return true;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
bool vec<D, T>::operator!=(const vec<inD, inT> &v) const {
    for (uint8_t i = 0; i < D; i++)
        if (this->data[i] == v.data[i])
            return false;
    return true;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
bool vec<D, T>::operator>(const vec<inD, inT> &v) const {
    return false;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
bool vec<D, T>::operator<(const vec<inD, inT> &v) const {
    return false;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
bool vec<D, T>::operator>=(const vec<inD, inT> &v) const {
    return false;
}

template <uint8_t D, typename T>
template <uint8_t inD, typename inT>
bool vec<D, T>::operator<=(const vec<inD, inT> &v) const {
    return false;
}

// Other Operators

template <uint8_t D, typename T> T vec<D, T>::operator[](uint8_t i) const {
    return this->data[i % D];
}

template <uint8_t D, typename T> T &vec<D, T>::operator[](uint8_t i) {
    return this->data[i % D];
}

template <uint8_t D, typename T> void vec<D, T>::operator++() { *this += 1.0f; }

template <uint8_t D, typename T> void vec<D, T>::operator--() { *this -= 1.0f; }

// Functions (Instance Methods)

template <uint8_t D, typename T> T vec<D, T>::length() const {
    return sqrtf(dot(*this, *this));
}

template <uint8_t D, typename T> vec<D, T> vec<D, T>::normalize() const {
    return *this / this->length();
}

template <uint8_t D, typename T>
vec<D, T> vec<D, T>::clamp(vec<D, T> min, vec<D, T> max) const {
    vec<D, T> out;

    for (uint8_t i = 0; i < D; i++) {
        if (this->data[i] < min.data[i])
            out.data[i] = min.data[i];
        else if (this->data[i] > max.data[i])
            out.data[i] = max.data[i];
        else
            out.data[i] = this->data[i];
    }

    return out;
}

// Functions (Static)

template <uint8_t D, typename T> T vec<D, T>::distance(vec a, vec b) {
    T out;

    vec<D, T> dist = a - b;
    for (uint8_t i = 0; i < D; i++)
        out += dist[i] * dist[i];

    return sqrt(out);
}

template <uint8_t D, typename T> T vec<D, T>::dot(vec a, vec b) {
    T out;

    for (uint8_t i = 0; i < D; i++)
        out += a[i] * b[i];

    return out;
}

template <uint8_t D, typename T>
vec<D, T> vec<D, T>::lerp(vec<D, T> a, vec<D, T> b, T blend) {
    vec<D, T> out;

    for (uint8_t i = 0; i < D; i++)
        out[i] = a.data[i] + (b.data[i] - a.data[i]) * blend;

    return out;
}

// Functions (Dimension-Specific)

template <uint8_t D, typename T> vec<3> vec<D, T>::cross(vec<3> a, vec<3> b) {
    return std::vector<T>({a.data[1] * b.data[2] - a.data[2] * b.data[1],
                           a.data[2] * b.data[0] - a.data[0] * b.data[2],
                           a.data[0] * b.data[1] - a.data[1] * b.data[0]});
}