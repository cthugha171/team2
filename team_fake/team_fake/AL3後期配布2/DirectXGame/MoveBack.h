#pragma once
#include "Input.h"
#include "Object3d.h"
class MoveBack
{
public:
	MoveBack(Object3d* obj);

	void Move(Input* input);

	void Draw();

private:
	DirectX::XMFLOAT3 rotate;
	Object3d* obj;
};

