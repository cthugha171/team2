#pragma once
#include "Input.h"
#include "Object3d.h"
#include "Camera.h"

class MoveBack
{
public:
	MoveBack(Object3d* obj);

	void Move(Input* input,Camera*camera);

	void Draw();

private:
	DirectX::XMFLOAT3 rotate;
	Object3d* obj;
};

