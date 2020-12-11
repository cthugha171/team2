#include "Vector2.h"
#include <cmath>

//デフォルトコンストラクタ
Vector2::Vector2() :
	x(0), y(0)
{
}
//コンストラクタ
Vector2::Vector2(float X, float Y)
	: x(X), y(Y)
{
}
//長さ
float Vector2::length() const
{
	return (float)std::sqrtf(x * x + y * y);
}
//正規化
Vector2 & Vector2::normalize()
{
	float len;

	if ((len = length()) != 0)
		*this /= len;

	return *this;
}
//内積
float Vector2::dot(const Vector2 & v) const
{
	return  x * v.x + y * v.y;
}
//外積
float Vector2::cross(const Vector2 & v) const
{
	return x * v.y - y * v.x;
}
//線形補間
Vector2 Vector2::lerp( const Vector2& end, const float time)
{
	x += (end.x - x)* time;
	y += (end.x - y)* time;
	return *this;

}
//始点と終点の線形補間
float Vector2::lerp(const float start, const float end, const float time)
{
	return (1 - time) * start + time * end;
}

//単項演算子オーバーロード＋
Vector2 Vector2::operator+() const
{
	return *this;
}
//単項演算子オーバーロードー
Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}
//代入演算子＋
Vector2 & Vector2::operator+=(const Vector2 & v)
{
	x += v.x;
	y += v.y;
	return *this;
}
//代入演算子ー
Vector2 & Vector2::operator-=(const Vector2 & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
//代入演算子＊
Vector2 & Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}
//代入演算子/
Vector2 & Vector2::operator/=(float s)
{
	if (s == 0)
	{
		x = x;
		y = y;
	}
	else
	{
		x /= s;
		y /= s;
	}

	return *this;
}


//二項演算子＋
const Vector2 operator+(const Vector2 & v1, const Vector2 & v2)
{
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}
//二項演算子ー
const Vector2 operator-(const Vector2 & v1, const Vector2 & v2)
{
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}
//二項演算子＊
const Vector2 operator*(const Vector2 & v, float s)
{
	return Vector2(v.x *s, v.y*s);
}
//二項演算子＊
const Vector2 operator*(float s, const Vector2 & v)
{
	return Vector2(v.x *s, v.y*s);
}
//二項演算子/
const Vector2 operator/(const Vector2 & v, float s)
{
	return  Vector2(v.x / s, v.y / s);
}
