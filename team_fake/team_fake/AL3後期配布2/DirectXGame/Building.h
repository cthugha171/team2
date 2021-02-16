#pragma once
#include "Camera.h"
#include "Object3d.h"
#include "Model.h"
#include "Player.h"
#include "Collision.h"
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "CollisionPrimitive.h"


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
	XMFLOAT3 position;//2つのオブジェクトの中点
	XMFLOAT3 dist;//中点までの距離
	Object3d* obj;
	Object3d* obj2;
	Collision* col;

	Rectangles* rect;
	Rectangles* rect2;
};