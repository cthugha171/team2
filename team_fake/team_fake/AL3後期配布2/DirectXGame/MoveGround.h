#pragma once
#include "Object3d.h"
#include "Camera.h"

class MoveGround
{
public:
	void Initialize(Object3d* obj,Object3d* obj2, float speed);

	void Update(Camera*camera);

	void Draw();

private:
	Object3d* first;
	Object3d* second;
	XMFLOAT3 firstPos;
	XMFLOAT3 secondPos;
};

