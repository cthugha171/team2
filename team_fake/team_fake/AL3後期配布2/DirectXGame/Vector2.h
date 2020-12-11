#pragma once
#ifndef _VECTOR2_H_
#define _VECTOR2_H_


struct Vector2
{
	float   x;
	float   y;

	//コンストラクタ
	Vector2();
	Vector2(float X, float Y);
	//メンバ関数
	float length() const;               //ノルムを求める
	Vector2& normalize();               //正規化する
	float dot(const Vector2& v) const;  //内積を求める
	float cross(const Vector2& v)const; //外積を求める
	//線形補間
	Vector2 lerp(const Vector2& end, const float time);
	//これはVector2とは関係なく線形補完する
	static float lerp(const float start, const float end, const float time);
	//単項演算子オーバーロード
	Vector2 operator + ()const;
	Vector2 operator - ()const;
	//代入演算子オーバーロード
	Vector2& operator += (const Vector2& v);
	Vector2& operator -= (const Vector2& v);
	Vector2& operator *= (float s);
	Vector2& operator /= (float s);
};

//二項演算子オーバーロード
const Vector2 operator + (const Vector2& v1, const Vector2& v2);
const Vector2 operator - (const Vector2& v1, const Vector2& v2);
const Vector2 operator * (const Vector2& v, float s);
const Vector2 operator * (float s, const Vector2& v);
const Vector2 operator / (const Vector2& v, float s);



#endif // !_VECTOR2_H_