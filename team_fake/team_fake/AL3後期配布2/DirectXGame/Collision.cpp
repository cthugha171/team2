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
