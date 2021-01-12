#pragma once
#include "Camera.h"
#include "Object3d.h"
#include "Model.h"
#include "Player.h"
#include "Collision.h"


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

	void Initialize(state state,XMFLOAT2 pos, Object3d* obj, Object3d* obj2);

	void Update(Camera* camera);

	void Draw();

	bool Collitions(Player* player,Model*mod);

	XMFLOAT3 GetPosition();

private:
	XMFLOAT3 position;
	Object3d* obj;
	Object3d* obj2;
	Collision* col;
};