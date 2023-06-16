#include <vector.hpp>

// -------- Vec2 --------

// vec2 ---- Constructors

// vec2(x, y) Constructor
vec2::vec2(float x, float y) { this->x = x, this->y = y; }

// vec2({x, y}) Constructor
vec2::vec2(float v[2]) { this->x = v[0], this->y = v[1]; }

// vec2(xy) Constructor
vec2::vec2(float v) { this->x = this->y = v; }

// vec2 ---- Operator Overloading (vec2)

// [+] vec2::operator (vec2)
vec2 vec2::operator+(const vec2 v) const {
    vec2 ret;
    ret.p[0] = this->p[0] + v.p[0];
    ret.p[1] = this->p[1] + v.p[1];
    return ret;
}

// [-] vec2::operator (vec2)
vec2 vec2::operator-(const vec2 v) const {
    vec2 ret;
    ret.p[0] = this->p[0] - v.p[0];
    ret.p[1] = this->p[1] - v.p[1];
    return ret;
}

// [*] vec2::operator (vec2)
vec2 vec2::operator*(const vec2 v) const {
    vec2 ret;
    ret.p[0] = this->p[0] * v.p[0];
    ret.p[1] = this->p[1] * v.p[1];
    return ret;
}

// [/] vec2::operator (vec2)
vec2 vec2::operator/(const vec2 v) const {
    vec2 ret;
    ret.p[0] = this->p[0] / v.p[0];
    ret.p[1] = this->p[1] / v.p[1];
    return ret;
}

// [+=] vec2::operator (vec2)
void vec2::operator+=(const vec2 v) {
    this->p[0] += v.p[0];
    this->p[1] += v.p[1];
}

// [-=] vec2::operator (vec2)
void vec2::operator-=(const vec2 v) {
    this->p[0] -= v.p[0];
    this->p[1] -= v.p[1];
}

// [*=] vec2::operator (vec2)
void vec2::operator*=(const vec2 v) {
    this->p[0] *= v.p[0];
    this->p[1] *= v.p[1];
}

// [/=] vec2::operator (vec2)
void vec2::operator/=(const vec2 v) {
    this->p[0] /= v.p[0];
    this->p[1] /= v.p[1];
}

// [=] vec2::operator (vec2)
void vec2::operator=(const vec2 v) {
    this->p[0] = v.p[0];
    this->p[1] = v.p[1];
}

// [==] vec2::operator (vec2)
bool vec2::operator==(const vec2 v) const {
    return this->p[0] == v.p[0] && this->p[1] == v.p[1];
}

// [!=] vec2::operator (vec2)
bool vec2::operator!=(const vec2 v) const {
    return this->p[0] != v.p[0] || this->p[1] != v.p[1];
}

// vec2 ---- Operator Overloading (float)

// [+] Operator (float)
vec2 vec2::operator+(const float v) const {
    vec2 ret;
    ret.p[0] = this->p[0] + v;
    ret.p[1] = this->p[1] + v;
    return ret;
}

// [-] Operator (float)
vec2 vec2::operator-(const float v) const {
    vec2 ret;
    ret.p[0] = this->p[0] - v;
    ret.p[1] = this->p[1] - v;
    return ret;
}

// [*] Operator (float)
vec2 vec2::operator*(const float v) const {
    vec2 ret;
    ret.p[0] = this->p[0] * v;
    ret.p[1] = this->p[1] * v;
    return ret;
}

// [/] Operator (float)
vec2 vec2::operator/(const float v) const {
    vec2 ret;
    ret.p[0] = this->p[0] / v;
    ret.p[1] = this->p[1] / v;
    return ret;
}

// [+=] Operator (float)
void vec2::operator+=(const float v) {
    this->p[0] += v;
    this->p[1] += v;
}

// [-=] Operator (float)
void vec2::operator-=(const float v) {
    this->p[0] -= v;
    this->p[1] -= v;
}

// [*=] Operator (float)
void vec2::operator*=(const float v) {
    this->p[0] *= v;
    this->p[1] *= v;
}

// [/=] Operator (float)
void vec2::operator/=(const float v) {
    this->p[0] /= v;
    this->p[1] /= v;
}

// [=] Operator (float)
void vec2::operator=(const float v) {
    this->p[0] = v;
    this->p[1] = v;
}

// [==] Operator (float)
bool vec2::operator==(const float v) const {
    return this->p[0] == v && this->p[1] == v;
}

// [!=] Operator (float)
bool vec2::operator!=(const float v) const {
    return this->p[0] != v || this->p[1] != v;
}

// vec2 ---- Indexing

// vec2[id] Get Operator
float vec2::operator[](int i) const { return this->p[i % 2]; }

// vec2[id] Set Operator
float &vec2::operator[](int i) { return this->p[i % 2]; }

// vec2 ---- Functions

// Avarage
// vec2 vec2::avg(unsigned int n, ...) {
//     va_list l;
//     va_start(l, n);

//     vec2 sum;
//     for (int i = 0; i < n; i++)
//         sum += va_arg(l, vec2);

//     return sum / n;
// }

// Dot Product
float vec2::dot(vec2 v) { return this->x * v.x + this->y * v.y; }

// Cross Product
vec2 vec2::cross(vec2 v) { return this->x * v.y - this->y * v.x; }

// Length
float vec2::length() { return sqrtf(this->dot(*this)); }

// Distance
float vec2::distance(vec2 v) {
    vec2 dist = *this - v;
    return sqrt(dist.x * dist.x + dist.y * dist.y);
}

// Normalize
vec2 vec2::normalize() { return *this / this->length(); }

// Get Data
float *vec2::data() { return &x; }

// -------- Vec3 --------

// vec3 ---- Constructors

// vec3(x, y, z) Constructor
vec3::vec3(float x, float y, float z) { this->x = x, this->y = y, this->z = z; }

// vec3({x, y, z}) Constructor
vec3::vec3(float v[3]) { this->x = v[0], this->y = v[1], this->z = v[2]; }

// vec3(xyz) Constructor
vec3::vec3(float v) { this->x = v, this->y = v, this->z = v; }

// vec3 ---- Operator Overloading (vec3)

// [+] Operator (vec2)
vec3 vec3::operator+(const vec3 v) const {
    vec3 ret;
    ret.p[0] = this->p[0] + v.p[0];
    ret.p[1] = this->p[1] + v.p[1];
    ret.p[2] = this->p[2] + v.p[2];
    return ret;
}

// [-] Operator (vec3)
vec3 vec3::operator-(const vec3 v) const {
    vec3 ret;
    ret.p[0] = this->p[0] - v.p[0];
    ret.p[1] = this->p[1] - v.p[1];
    ret.p[2] = this->p[2] - v.p[2];
    return ret;
}

// [*] Operator (vec3)
vec3 vec3::operator*(const vec3 v) const {
    vec3 ret;
    ret.p[0] = this->p[0] * v.p[0];
    ret.p[1] = this->p[1] * v.p[1];
    ret.p[2] = this->p[2] * v.p[2];
    return ret;
}

// [/] Operator (vec3)
vec3 vec3::operator/(const vec3 v) const {
    vec3 ret;
    ret.p[0] = this->p[0] / v.p[0];
    ret.p[1] = this->p[1] / v.p[1];
    ret.p[2] = this->p[2] / v.p[2];
    return ret;
}

// [+=] Operator (vec3)
void vec3::operator+=(const vec3 v) {
    this->p[0] += v.p[0];
    this->p[1] += v.p[1];
    this->p[2] += v.p[2];
}

// [-=] Operator (vec3)
void vec3::operator-=(const vec3 v) {
    this->p[0] -= v.p[0];
    this->p[1] -= v.p[1];
    this->p[2] -= v.p[2];
}

// [*=] Operator (vec3)
void vec3::operator*=(const vec3 v) {
    this->p[0] *= v.p[0];
    this->p[1] *= v.p[1];
    this->p[2] *= v.p[2];
}

// [/=] Operator (vec3)
void vec3::operator/=(const vec3 v) {
    this->p[0] /= v.p[0];
    this->p[1] /= v.p[1];
    this->p[2] /= v.p[2];
}

// [=] Operator (vec3)
void vec3::operator=(const vec3 v) {
    this->p[0] = v.p[0];
    this->p[1] = v.p[1];
    this->p[2] = v.p[2];
}

// [==] Operator (vec3)
bool vec3::operator==(const vec3 v) const {
    return this->p[0] == v.p[0] && this->p[1] == v.p[1] && this->p[2] == v.p[2];
}

// [!=] Operator (vec3)
bool vec3::operator!=(const vec3 v) const {
    return this->p[0] != v.p[0] || this->p[1] != v.p[1] || this->p[2] != v.p[2];
}

// vec3 ---- Operator Overloading (float)

// [+] Operator (float)
vec3 vec3::operator+(const float v) const {
    vec3 ret;
    ret.p[0] = this->p[0] + v;
    ret.p[1] = this->p[1] + v;
    ret.p[2] = this->p[2] + v;
    return ret;
}

// [-] Operator (float)
vec3 vec3::operator-(const float v) const {
    vec3 ret;
    ret.p[0] = this->p[0] - v;
    ret.p[1] = this->p[1] - v;
    ret.p[2] = this->p[2] - v;
    return ret;
}

// [*] Operator (float)
vec3 vec3::operator*(const float v) const {
    vec3 ret;
    ret.p[0] = this->p[0] * v;
    ret.p[1] = this->p[1] * v;
    ret.p[2] = this->p[2] * v;
    return ret;
}

// [/] Operator (float)
vec3 vec3::operator/(const float v) const {
    vec3 ret;
    ret.p[0] = this->p[0] / v;
    ret.p[1] = this->p[1] / v;
    ret.p[2] = this->p[2] / v;
    return ret;
}

// [+=] Operator (float)
void vec3::operator+=(const float v) {
    this->p[0] += v;
    this->p[1] += v;
    this->p[2] += v;
}

// [-=] Operator (float)
void vec3::operator-=(const float v) {
    this->p[0] -= v;
    this->p[1] -= v;
    this->p[2] -= v;
}

// [*=] Operator (float)
void vec3::operator*=(const float v) {
    this->p[0] *= v;
    this->p[1] *= v;
    this->p[2] *= v;
}

// [/=] Operator (float)
void vec3::operator/=(const float v) {
    this->p[0] /= v;
    this->p[1] /= v;
    this->p[2] /= v;
}

// [=] Operator (float)
void vec3::operator=(const float v) {
    this->p[0] = v;
    this->p[1] = v;
    this->p[2] = v;
}

// [==] Operator (float)
bool vec3::operator==(const float v) const {
    return this->p[0] == v && this->p[1] == v && this->p[2] == v;
}

// [!=] Operator (float)
bool vec3::operator!=(const float v) const {
    return this->p[0] != v || this->p[1] != v || this->p[2] != v;
}

// vec3 ---- Indexing

// vec2[id] Get Operator
float vec3::operator[](int i) const { return this->p[i % 3]; }

// vec2[id] Set Operator
float &vec3::operator[](int i) { return this->p[i % 3]; }

// vec3 ---- Functions

// Avarage
// vec3 vec3::avg(unsigned int n, ...) {
//     va_list l;
//     va_start(l, n);

//     vec3 sum;
//     for (int i = 0; i < n; i++)
//         sum += va_arg(l, vec3);

//     return sum / n;
// }

// Dot Product
float vec3::dot(vec3 v) {
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

// Cross Product
vec3 vec3::cross(vec3 v) {
    return {this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z,
            this->x * v.y - this->y * v.x};
}

// Length
float vec3::length() { return sqrtf(this->dot(*this)); }

// Distance
float vec3::distance(vec3 v) {
    vec3 dist = *this - b;
    return sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);
}

// Normalize
vec3 vec3::normalize() { return *this / this->length(); }

// Get Data
float *vec3::data() { return &x; }