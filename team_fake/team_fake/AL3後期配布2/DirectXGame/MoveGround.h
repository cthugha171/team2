#pragma once
#include "Object3d.h"
#include "Camera.h"

class MoveGround
{
public:
	void Initialize(Object3d* obj, float speed);

	void Update(Camera*camera);

	void Draw();
};

