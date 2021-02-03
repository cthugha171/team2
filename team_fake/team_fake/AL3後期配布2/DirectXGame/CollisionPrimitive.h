#pragma once
/// <summary>
/// 当たり判定プリミティブ
/// </summary>

#include <DirectXMath.h>

/// <summary>
/// 球
/// </summary>
struct Sphere
{
	// 中心座標
	DirectX::XMVECTOR center = {};
	// 半径
	float radius = 1.0f;
};

/// <summary>
/// 平面
/// </summary>
struct Plane
{
	// 法線ベクトル
	DirectX::XMVECTOR normal = { 0,1,0 };
	// 原点(0,0,0)からの距離
	float distance = 0.0f;
};

/// <summary>
/// 矩形
/// </summary>
struct Rectangles
{
	//中心点
	DirectX::XMFLOAT3 center{ 0,0,0 };
	//矩形のサイズ
	DirectX::XMFLOAT3 size{ 10.0f,10.0f,10.0f };
};