#pragma once
#include "Camera.h"
#include "Object3d.h"
#include "Model.h"
#include "Player.h"
#include "Collision.h"
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>


enum state 
{
	high,
	mid,
	low,
};

class player;

class Building
{
public:

	void Initialize(state state,XMFLOAT2 pos,XMFLOAT3 dist, Object3d* obj, Object3d* obj2);

	void Update(Camera* camera);

	void Draw();

	bool Collitions(Player* player,Model*mod);

	XMFLOAT3 GetPosition();

private:
	XMFLOAT3 position;//2�̃I�u�W�F�N�g�̒��_
	XMFLOAT3 dist;//���_�܂ł̋���
	Object3d* obj;
	Object3d* obj2;
	Collision* col;
};