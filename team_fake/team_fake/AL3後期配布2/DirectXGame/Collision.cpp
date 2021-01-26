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
	for (auto i = 0; i != indices.size(); i=i+3)
	{ 
		XMFLOAT3* pos0 = &vertices[indices[i]].pos;
		XMFLOAT3* pos1 = &vertices[indices[i+1]].pos;
		XMFLOAT3* pos2 = &vertices[indices[i+2]].pos;

		XMVECTOR p0 = XMLoadFloat3(pos0);
		XMVECTOR p1 = XMLoadFloat3(pos1);
		XMVECTOR p2 = XMLoadFloat3(pos2);
		XMVECTOR center = XMLoadFloat3(point);
		// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
		XMVECTOR p0_p1 = p1 - p0;
		XMVECTOR p0_p2 = p2 - p0;
		XMVECTOR p0_pt = center - p0;

		XMVECTOR d1 = XMVector3Dot(p0_p1, p0_pt);
		XMVECTOR d2 = XMVector3Dot(p0_p2, p0_pt);

		if (d1.m128_f32[0] <= 0.0f && d2.m128_f32[0] <= 0.0f)
		{
			// p0���ŋߖT
			*closest = p0;
			return;
		}

		// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
		XMVECTOR p1_pt = center - p1;

		XMVECTOR d3 = XMVector3Dot(p0_p1, p1_pt);
		XMVECTOR d4 = XMVector3Dot(p0_p2, p1_pt);

		if (d3.m128_f32[0] >= 0.0f && d4.m128_f32[0] <= d3.m128_f32[0])
		{
			// p1���ŋߖT
			*closest = p1;
			return;
		}

		// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
		float vc = d1.m128_f32[0] * d4.m128_f32[0] - d3.m128_f32[0] * d2.m128_f32[0];
		if (vc <= 0.0f && d1.m128_f32[0] >= 0.0f && d3.m128_f32[0] <= 0.0f)
		{
			float v = d1.m128_f32[0] / (d1.m128_f32[0] - d3.m128_f32[0]);
			*closest = p0 + v * p0_p1;
			return;
		}

		// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
		XMVECTOR p2_pt = center - p2;

		XMVECTOR d5 = XMVector3Dot(p0_p1, p2_pt);
		XMVECTOR d6 = XMVector3Dot(p0_p2, p2_pt);
		if (d6.m128_f32[0] >= 0.0f && d5.m128_f32[0] <= d6.m128_f32[0])
		{
			*closest = p2;
			return;
		}

		// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
		float vb = d5.m128_f32[0] * d2.m128_f32[0] - d1.m128_f32[0] * d6.m128_f32[0];
		if (vb <= 0.0f && d2.m128_f32[0] >= 0.0f && d6.m128_f32[0] <= 0.0f)
		{
			float w = d2.m128_f32[0] / (d2.m128_f32[0] - d6.m128_f32[0]);
			*closest = p0 + w * p0_p2;
			return;
		}

		// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
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
	//���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	XMFLOAT3* pos = &shpere->GetPosition();
	XMVECTOR vpos = XMLoadFloat3(pos);
	ClosestPtPoint2Triangle(pos, triangle, &p);
	//�_p�Ƌ��̒��S�̍����x�N�g��
	XMVECTOR v = p - vpos;
	//������2������߂�
	//(�����x�N�g�����m�̓��ς͎O�����̒藝�̃��[�g�����̎��ƈ�v����)
	v = XMVector3Dot(v, v);
	//���ƎO�p�`�̋��������a�����Ȃ瓖�����Ă��Ȃ�
	if (v.m128_f32[0] > shpere->GetRadius() * shpere->GetRadius())return false;
	//�^����_���v�Z
	if (inter) {
		//�O�p�`��̍ŋߐړ_p���^����_�Ƃ���
		*inter = p;
	}
	return true;
}

bool Collision::SphereToPlane(Object3d* shpere, Model* plane,XMFLOAT3 *inter )
{
	//XMFLOAT3 pos = shpere->GetPosition();
	//XMFLOAT3 normal = plane->GetNormal();
	////���W�n�̌��_���狅�̒��S���W�ւ̋���
	//float distV = pos.x * normal.x + pos.y * normal.y + pos.z * normal.z;
	//float dist = distV - 0.0;
	//if (fabs(dist) > shpere->GetRadius()) return false;
	//if (inter)
	//{
	//	*inter = -dist * normal + pos;
	//}
	return true;
}
