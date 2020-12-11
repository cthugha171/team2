#include "Vector3.h"
#include <cmath>

Vector3::Vector3() 
	:x(0),y(0),z(0)
{

}
Vector3::Vector3(float X, float Y, float Z) 
	:x(X),y(Y),z(Z)
{

}
float Vector3::length()const
{
	return std::sqrtf(x * x + y * y + z * z);
}

Vector3 & Vector3::normalize()
{
	// TODO: return ステートメントをここに挿入します
	float L = length();
	if (L == 0) {
		return *this;
	}
	return *this /= L;
}

float Vector3::dot(const Vector3 & v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3 & v) const
{
	return Vector3(y*v.z - z * v.y, z*v.x - x * v.z, y*v.x - x * v.y);
}

Vector3 Vector3::operator+() const
{
	return *this;
}

Vector3 Vector3::operator-() const
{
	return { -x,-y,-z };
}

Vector3 & Vector3::operator+=(const Vector3 & v)
{
	// TODO: return ステートメントをここに挿入します
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 & Vector3::operator-=(const Vector3 & v)
{
	// TODO: return ステートメントをここに挿入します
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 & Vector3::operator*=(float s)
{

	// TODO: return ステートメントをここに挿入します
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3 & Vector3::operator/=(float s)
{
	if (s == 0) {
		return *this;
	}
	// TODO: return ステートメントをここに挿入します
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

const Vector3 operator+(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

const Vector3 operator-(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

const Vector3 operator*(const Vector3 & v, float s)
{
	return Vector3(v.x*s, v.y*s, v.z*s);
}

const Vector3 operator*(float s, const Vector3 & v)
{
	return Vector3(v.x*s, v.y*s, v.z*s);
}

const Vector3 operator/(const Vector3 & v, float s)
{
	//sが0だと割ったとき永遠の0になるので条件追加
	if (s == 0) {
		return v;
	}
	return Vector3(v.x / s, v.y / s, v.z / s);
}
