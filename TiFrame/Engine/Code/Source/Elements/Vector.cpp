#include <Elements/Vector.h>
#include <cmath>
#include <Static/Math.h>
using namespace Ti;

//<!-- Vec3
Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(float xyz) : x(xyz), y(xyz), z(xyz) {}
Vec3::Vec3(Vec2 xy, float _z) : x(xy.x), y(xy.y), z(_z) {}
Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 Vec3::operator+(const Vec3& v) const
{
	Vec3 tempVec;
	tempVec.x = v.x + x;
	tempVec.y = v.y + y;
	tempVec.z = v.z + z;
	return tempVec;
}
Vec3 Vec3::operator-(const Vec3& v) const
{
	Vec3 tempVec;
	tempVec.x = x - v.x;
	tempVec.y = y - v.y;
	tempVec.z = z - v.z;
	return tempVec;
}
Vec3 Vec3::operator*(const float value) const
{
	Vec3 tempVec;
	tempVec.x = value *  x;
	tempVec.y = value *  y;
	tempVec.z = value *  z;
	return tempVec;
}

Vec3 Vec3::operator/(const float value) const
{
	const float inv = 1 / value;

	Vec3 tempVec;
	tempVec.x = x * inv;
	tempVec.y = y * inv;
	tempVec.z = z * inv;
	return tempVec;
}

Vec3 Vec3::operator%(const float value) const
{

	Vec3 tempVec;
	tempVec.x = Math::Mod(x, value);
	tempVec.y = Math::Mod(y, value);
	tempVec.z = Math::Mod(z, value);
	return tempVec;
}

Vec3 Vec3::operator-() const
{
	Vec3 tempVec;
	tempVec.x = -1 * x;
	tempVec.y = -1 * y;
	tempVec.z = -1 * z;
	return tempVec;
}
Vec3 Vec3::operator*(const Vec3 & vector) const
{
	Vec3 tempVec;
	tempVec.x = x * vector.x;
	tempVec.y = y * vector.y;
	tempVec.z = z * vector.z;
	return tempVec;
}
Vec3 Vec3::operator/(const Vec3 & vector) const
{
	Vec3 tempVec;
	tempVec.x = x / vector.x;
	tempVec.y = y / vector.y;
	tempVec.z = z / vector.z;
	return tempVec;
}
void Vec3::operator+=(const Vec3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
void Vec3::operator-=(const Vec3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
void Vec3::operator*=(const float value)
{
	x *= value;
	y *= value;
	z *= value;
}

void Vec3::operator*=(const Vec3 &value) {
	x *= value.x;
	y *= value.y;
	z *= value.z;
}

Vec3 Vec3::Cross(const Vec3 & vector) const
{
	return Vec3(
		y * vector.z - z * vector.y,
		z * vector.x - x * vector.z,
		x * vector.y - y * vector.x);
}

float Vec3::Dot(const Vec3 & vector) const
{
	return  x * vector.x + y * vector.y + z * vector.z;
}

float Vec3::Magnitude() const
{
	return std::sqrt(x *  x + y *  y + z *  z);
}

float Vec3::SquareMagnitude() const
{
	return (x * x + y * y + z * z);
}

Vec3 Vec3::Normalize() const
{
	float mag = Magnitude();
	if (mag == 0) return Vec3(1,0,0);
	return *this / mag;
}

//Vec3 Vec3::normalize() const {
//	float m = Magnitude();
//	if (m == 0) return Vec3();
//	return *this / m;
//}

bool Vec3::operator==(const Vec3 & other) const
{
	return  x == other.x &&  y == other.y &&  z == other.z;
}

bool Vec3::operator!=(const Vec3 & other) const
{
	return  x != other.x || y != other.y || z != other.z;;
}

Vec3 Vec3::Clamp(float min, float max)
{
	Vec3 ni = *this;

	if (ni.x < min)
		ni.x = min;
	if (ni.x > max)
		ni.x = max;

	if (ni.y < min)
		ni.y = min;
	if (ni.y > max)
		ni.y = max;

	if (ni.z < min)
		ni.z = min;
	if (ni.z > max)
		ni.z = max;

	return ni;
}


Vec3 Slerp(Vec3 start, Vec3 end, float percent)
{
	//float dot = start.Dot(end);
	//dot.Clamp(-1.0f, 1.0f);
	//float alpha = Mathf.Acos(dot)*percent;
	//Vec3 RelativeVec = end - start*dot;
	//RelativeVec.Normalize();

	return Vec3();
	//((start*Mathf.Cos(alpha)) + (RelativeVec*Mathf.Sin(alpha)));
}

Vec3 Vec3::fract() const {
	return Vec3(Math::Fract(x), Math::Fract(y), Math::Fract(z));
}

Vec3 Vec3::floor() const {
	return Vec3(Math::Floor(x), Math::Floor(y), Math::Floor(z));
}

Vec3 Vec3::sqrt() const {
	return Vec3(Math::Sqrt(x), Math::Sqrt(y), Math::Sqrt(z));
}

Vec3 Vec3::min(Vec3 a, Vec3 b) {
	return Vec3(Math::Min(a.x, b.x), Math::Min(a.y, b.y), Math::Min(a.z, b.z));
}

Vec3 Vec3::max(Vec3 a, Vec3 b) {
	return Vec3(Math::Max(a.x, b.x), Math::Max(a.y, b.y), Math::Max(a.z, b.z));
}

Vec2 Vec3::xy() { return Vec2(x, y); }
void Vec3::xy(Vec2 xy) { x = xy.x; y = xy.y; }

Vec2 Vec3::xz() { return Vec2(x, z); }
void Vec3::xz(Vec2 xz) { x = xz.x; z = xz.y; }

Vec2 Vec3::yz() { return Vec2(y, z); }
void Vec3::yz(Vec2 yz) { y = yz.x; z = yz.y; }

Vec2 Vec3::yx() { return Vec2(y, x); }
void Vec3::yx(Vec2 xy) { x = xy.y; y = xy.x; }

Vec2 Vec3::zx() { return Vec2(z, x); }
void Vec3::zx(Vec2 xz) { x = xz.y; z = xz.x; }

Vec2 Vec3::zy() { return Vec2(z, y); }
void Vec3::zy(Vec2 yz) { y = yz.y; z = yz.x; }

//<!-- Vec4

Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
Vec4::Vec4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
Vec4::Vec4(Vec3 xyz, float _w) : x(xyz.x), y(xyz.y), z(xyz.z), w(_w) {}
Vec4::Vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

Vec4 Vec4::operator+(const Vec4 &v) const {
	Vec4 tempVec;
	tempVec.x = v.x + x;
	tempVec.y = v.y + y;
	tempVec.z = v.z + z;
	tempVec.w = v.w + w;
	return tempVec;
}
Vec4 Vec4::operator-(const Vec4 &v) const {
	Vec4 tempVec;
	tempVec.x = x - v.x;
	tempVec.y = y - v.y;
	tempVec.z = z - v.z;
	tempVec.w = w - v.w;
	return tempVec;
}
Vec4 Vec4::operator*(const float value) const {
	Vec4 tempVec;
	tempVec.x = value *  x;
	tempVec.y = value *  y;
	tempVec.z = value *  z;
	tempVec.w = value *  w;
	return tempVec;
}

Vec4 Vec4::operator-() const {
	Vec4 tempVec;
	tempVec.x = -1 * x;
	tempVec.y = -1 * y;
	tempVec.z = -1 * z;
	tempVec.w = -1 * w;
	return tempVec;
}
Vec4 Vec4::operator*(const Vec4 &vector) const {
	Vec4 tempVec;
	tempVec.x = vector.x *  x;
	tempVec.y = vector.y *  y;
	tempVec.z = vector.z *  z;
	tempVec.w = vector.w *  w;
	return tempVec;
}
void Vec4::operator+=(const Vec4 & v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}
void Vec4::operator-=(const Vec4 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}
void Vec4::operator*=(const float value) {
	x *= value;
	y *= value;
	z *= value;
	w *= value;
}

void Vec4::operator*=(const Vec4 &value) {
	x *= value.x;
	y *= value.y;
	z *= value.z;
	w *= value.w;
}

bool Vec4::operator==(const Vec4 & other) const {
	return  x == other.x &&  y == other.y &&  z == other.z && w == other.w;
}

bool Vec4::operator!=(const Vec4 & other) const {
	return  x != other.x || y != other.y || z != other.z || w != other.w;
}

Vec4 Vec4::Clamp(float min, float max)
{
	Vec4 ni = *this;

	if (ni.x < min)
		ni.x = min;
	if (ni.x > max)
		ni.x = max;

	if (ni.y < min)
		ni.y = min;
	if (ni.y > max)
		ni.y = max;

	if (ni.z < min)
		ni.z = min;
	if (ni.z > max)
		ni.z = max;

	if (ni.w < min)
		ni.w = min;
	if (ni.w > max)
		ni.w = max;

	return ni;
}

Vec4 Vec4::fract() const {
	return Vec4(Math::Fract(x), Math::Fract(y), Math::Fract(z), Math::Fract(w));
}

Vec4 Vec4::floor() const {
	return Vec4(Math::Floor(x), Math::Floor(y), Math::Floor(z), Math::Fract(w));
}

Vec4 Vec4::min(Vec4 a, Vec4 b) {
	return Vec4(Math::Min(a.x, b.x), Math::Min(a.y, b.y), Math::Min(a.z, b.z), Math::Min(a.w, b.w));
}

Vec4 Vec4::max(Vec4 a, Vec4 b) {
	return Vec4(Math::Max(a.x, b.x), Math::Max(a.y, b.y), Math::Max(a.z, b.z), Math::Max(a.w, b.w));
}

//<!-- vec2

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float xy) : x(xy), y(xy) {}
Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}

Vec2 Vec2::operator+(const Vec2 &v) const {
	Vec2 tempVec;
	tempVec.x = v.x + x;
	tempVec.y = v.y + y;
	return tempVec;
}
Vec2 Vec2::operator-(const Vec2 &v) const {
	Vec2 tempVec;
	tempVec.x = x - v.x;
	tempVec.y = y - v.y;
	return tempVec;
}
Vec2 Vec2::operator*(const float value) const {
	Vec2 tempVec;
	tempVec.x = value *  x;
	tempVec.y = value *  y;
	return tempVec;
}

Vec2 Vec2::operator-() const {
	Vec2 tempVec;
	tempVec.x = -1 * x;
	tempVec.y = -1 * y;
	return tempVec;
}

Vec2 Vec2::operator*(const Vec2 &vector) const {
	Vec2 tempVec;
	tempVec.x = vector.x *  x;
	tempVec.y = vector.y *  y;
	return tempVec;
}

Vec2 Vec2::operator/(const Vec2 &vector) const {
	Vec2 tempVec;
	tempVec.x = x / vector.x;
	tempVec.y = y / vector.y;
	return tempVec;
}

void Vec2::operator+=(const Vec2 & v) {
	x += v.x;
	y += v.y;
}
void Vec2::operator-=(const Vec2 &v)
{
	x -= v.x;
	y -= v.y;
}
void Vec2::operator*=(const float value) {
	x *= value;
	y *= value;
}

void Vec2::operator*=(const Vec2 &value) {
	x *= value.x;
	y *= value.y;
}

Vec2 Vec2::operator/(const float value) const
{
	const float inv = 1 / value;

	Vec2 tempVec;
	tempVec.x = x * inv;
	tempVec.y = y * inv;
	return tempVec;
}

Vec2 Vec2::operator%(const float value) const
{

	Vec2 tempVec;
	tempVec.x = Math::Mod(x, value);
	tempVec.y = Math::Mod(y, value);
	return tempVec;
}

bool Vec2::operator==(const Vec2 & other) const {
	return  x == other.x &&  y == other.y;
}

bool Vec2::operator!=(const Vec2 & other) const {
	return  x != other.x || y != other.y;
}

Vec2 Vec2::Clamp(float min, float max)
{
	Vec2 ni = *this;

	if (ni.x < min)
		ni.x = min;
	if (ni.x > max)
		ni.x = max;

	if (ni.y < min)
		ni.y = min;
	if (ni.y > max)
		ni.y = max;

	return ni;
}

Vec2 Vec2::fract() const {
	return Vec2(Math::Fract(x), Math::Fract(y));
}

Vec2 Vec2::floor() const {
	return Vec2(Math::Floor(x), Math::Floor(y));
}

Vec2 Vec2::sqrt() const {
	return Vec2(Math::Sqrt(x), Math::Sqrt(y));
}

Vec2 Vec2::min(Vec2 a, Vec2 b) {
	return Vec2(Math::Min(a.x, b.x), Math::Min(a.y, b.y));
}

Vec2 Vec2::max(Vec2 a, Vec2 b) {
	return Vec2(Math::Max(a.x, b.x), Math::Max(a.y, b.y));
}