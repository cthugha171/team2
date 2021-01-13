#include "Collision.h"

DirectX::XMFLOAT3 operator*(float b,DirectX::XMFLOAT3& a)
{
	return XMFLOAT3(a.x * b, a.y * b, a.z * b);
}

 DirectX::XMFLOAT3 operator+( DirectX::XMFLOAT3 lhs,  DirectX::XMFLOAT3 rhs)
{
	XMFLOAT3 result;
	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	return result;
}

 DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 lhs, DirectX::XMFLOAT3 rhs)
 {
	 XMFLOAT3 result;
	 result.x = lhs.x - rhs.x;
	 result.y = lhs.y - rhs.y;
	 result.z = lhs.z - rhs.z;
	 return result;
 }

bool Collision::SphereToSphere( Object3d* shpere1,  Object3d* shpere2)
{
	XMFLOAT3 pos1= shpere1->GetPosition();
	XMFLOAT3 pos2 = shpere2->GetPosition();
	float r1 = shpere1->GetRadius();
	float r2 = shpere2->GetRadius();

	float x = powf( pos2.x - pos1.x, 2);
	float y = powf( pos2.y - pos1.y, 2);
	float z = powf( pos2.z - pos2.z, 2);
	float r = powf(r1 + r2,2);
	if (x + y + z <= r)
	{
		return true;
	}
	return false;
}

void Collision::ClosestPtPoint2Triangle(XMFLOAT3* point,Model* triangle, DirectX::XMVECTOR* closest)
{
	std::vector<Mesh::VertexPosNormalUv> vertices = triangle->Getvertices();
	std::vector<unsigned short> indices = triangle->Getindices();
	for (auto i = 0; i != indices.size()-2; ++i)
	{ 
		XMFLOAT3* pos0 = &vertices[indices[i]].pos;
		XMFLOAT3* pos1 = &vertices[indices[i+1]].pos;
		XMFLOAT3* pos2 = &vertices[indices[i+2]].pos;

		XMVECTOR p0 = XMLoadFloat3(pos0);
		XMVECTOR p1 = XMLoadFloat3(pos1);
		XMVECTOR p2 = XMLoadFloat3(pos2);
		XMVECTOR center = XMLoadFloat3(point);
		// pointがp0の外側の頂点領域の中にあるかどうかチェック
		XMVECTOR p0_p1 = p1 - p0;
		XMVECTOR p0_p2 = p2 - p0;
		XMVECTOR p0_pt = center - p0;

		XMVECTOR d1 = XMVector3Dot(p0_p1, p0_pt);
		XMVECTOR d2 = XMVector3Dot(p0_p2, p0_pt);

		if (d1.m128_f32[0] <= 0.0f && d2.m128_f32[0] <= 0.0f)
		{
			// p0が最近傍
			*closest = p0;
			return;
		}

		// pointがp1の外側の頂点領域の中にあるかどうかチェック
		XMVECTOR p1_pt = center - p1;

		XMVECTOR d3 = XMVector3Dot(p0_p1, p1_pt);
		XMVECTOR d4 = XMVector3Dot(p0_p2, p1_pt);

		if (d3.m128_f32[0] >= 0.0f && d4.m128_f32[0] <= d3.m128_f32[0])
		{
			// p1が最近傍
			*closest = p1;
			return;
		}

		// pointがp0_p1の辺領域の中にあるかどうかチェックし、あればpointのp0_p1上に対する射影を返す
		float vc = d1.m128_f32[0] * d4.m128_f32[0] - d3.m128_f32[0] * d2.m128_f32[0];
		if (vc <= 0.0f && d1.m128_f32[0] >= 0.0f && d3.m128_f32[0] <= 0.0f)
		{
			float v = d1.m128_f32[0] / (d1.m128_f32[0] - d3.m128_f32[0]);
			*closest = p0 + v * p0_p1;
			return;
		}

		// pointがp2の外側の頂点領域の中にあるかどうかチェック
		XMVECTOR p2_pt = center - p2;

		XMVECTOR d5 = XMVector3Dot(p0_p1, p2_pt);
		XMVECTOR d6 = XMVector3Dot(p0_p2, p2_pt);
		if (d6.m128_f32[0] >= 0.0f && d5.m128_f32[0] <= d6.m128_f32[0])
		{
			*closest = p2;
			return;
		}

		// pointがp0_p2の辺領域の中にあるかどうかチェックし、あればpointのp0_p2上に対する射影を返す
		float vb = d5.m128_f32[0] * d2.m128_f32[0] - d1.m128_f32[0] * d6.m128_f32[0];
		if (vb <= 0.0f && d2.m128_f32[0] >= 0.0f && d6.m128_f32[0] <= 0.0f)
		{
			float w = d2.m128_f32[0] / (d2.m128_f32[0] - d6.m128_f32[0]);
			*closest = p0 + w * p0_p2;
			return;
		}

		// pointがp1_p2の辺領域の中にあるかどうかチェックし、あればpointのp1_p2上に対する射影を返す
		float va = d3.m128_f32[0] * d6.m128_f32[0] - d5.m128_f32[0] * d4.m128_f32[0];
		if (va <= 0.0f && (d4.m128_f32[0] - d3.m128_f32[0]) >= 0.0f && (d5.m128_f32[0] - d6.m128_f32[0]) >= 0.0f)
		{
			float w = (d4.m128_f32[0] - d3.m128_f32[0]) / ((d4.m128_f32[0] - d3.m128_f32[0]) + (d5.m128_f32[0] - d6.m128_f32[0]));
			*closest = p1 + w * (p2 - p1);
			return;
		}

		float denom = 1.0f / (va + vb + vc);
		float v = vb * denom;
		float w = vc * denom;
		*closest = p0 + p0_p1 * v + p0_p2 * w;
	}

}

bool Collision::CheckSphere2Triangle(Object3d* shpere, Model* triangle, DirectX::XMVECTOR* inter)
{
	XMVECTOR p;
	//球の中心に対する最近接点である三角形上にある点pを見つける
	XMFLOAT3* pos = &shpere->GetPosition();
	XMVECTOR vpos = XMLoadFloat3(pos);
	ClosestPtPoint2Triangle(pos, triangle, &p);
	//点pと球の中心の差分ベクトル
	XMVECTOR v = p - vpos;
	//距離の2乗を求める
	//(同じベクトル同士の内積は三平方の定理のルート内部の式と一致する)
	v = XMVector3Dot(v, v);
	//球と三角形の距離が半径いかなら当たっていない
	if (v.m128_f32[0] > shpere->GetRadius() * shpere->GetRadius())return false;
	//疑似交点を計算
	if (inter) {
		//三角形上の最近接点pを疑似交点とする
		*inter = p;
	}
	return true;
}

bool Collision::SphereToPlane(Object3d* shpere, Model* plane,XMFLOAT3 *inter )
{
	//XMFLOAT3 pos = shpere->GetPosition();
	//XMFLOAT3 normal = plane->GetNormal();
	////座標系の原点から球の中心座標への距離
	//float distV = pos.x * normal.x + pos.y * normal.y + pos.z * normal.z;
	//float dist = distV - 0.0;
	//if (fabs(dist) > shpere->GetRadius()) return false;
	//if (inter)
	//{
	//	*inter = -dist * normal + pos;
	//}
	return true;
}
