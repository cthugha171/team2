#pragma once

#include "Object3d.h" 
#include "Model.h"
#include <DirectXMath.h>

using namespace DirectX;

class Collision
{
public:
	bool SphereToSphere( Object3d* shpere1,  Object3d* shpere2);
	bool SphereToPlane( Object3d* shpere, Model* plane, XMFLOAT3* inter);
};