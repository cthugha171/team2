#pragma once

#include "Object3d.h" 
#include "Model.h"
#include <DirectXMath.h>

using namespace DirectX;

class Collision
{
public:
	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="shpere1">3D�I�u�W�F�N�g</param>
	/// <param name="shpere2">3D�I�u�W�F�N�g</param>
	/// <returns>�������Ă��邩</returns>
	bool SphereToSphere( Object3d* shpere1,  Object3d* shpere2);

	/// <summary>
	/// �_�ƎO�p�`�̍ŋߐړ_�����߂�
	/// </summary>
	/// <param name="point">�_</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="closest">�ŋߐړ_</param>
	static void ClosestPtPoint2Triangle(XMFLOAT3* point, Model* triangle, DirectX::XMVECTOR* closest);
	static bool CheckSphere2Triangle(Object3d* shpere, Model* triangle,DirectX::XMVECTOR* inter = nullptr);

	bool SphereToPlane( Object3d* shpere, Model* plane, XMFLOAT3* inter);
};