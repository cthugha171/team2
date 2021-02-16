#pragma once

#include "Object3d.h" 
#include "Model.h"
#include <DirectXMath.h>

using namespace DirectX;

class Collision
{
public:
	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	/// <param name="shpere1">3Dオブジェクト</param>
	/// <param name="shpere2">3Dオブジェクト</param>
	/// <returns>当たっているか</returns>
	bool SphereToSphere( Object3d* shpere1,  Object3d* shpere2);

	/// <summary>
	/// 点と三角形の最近接点を求める
	/// </summary>
	/// <param name="point">点</param>
	/// <param name="triangle">三角形</param>
	/// <param name="closest">最近接点</param>
	static void ClosestPtPoint2Triangle(XMFLOAT3* point, Model* triangle, DirectX::XMVECTOR* closest);
	static bool CheckSphere2Triangle(Object3d* shpere, Model* triangle,DirectX::XMVECTOR* inter = nullptr);

	bool SphereToPlane( Object3d* shpere, Model* plane, XMFLOAT3* inter);

	/// <summary>
	/// 球と矩形の当たり判定
	/// </summary>
	/// <param name="sph">オブジェクトに設定されている球</param>
	/// <param name="rect">矩形</param>
	/// <returns>当たっているかどうか</returns>
	bool SphereToRectangles(Object3d* sph, Rectangles* rect);
};