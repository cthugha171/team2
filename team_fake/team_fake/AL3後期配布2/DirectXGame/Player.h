#pragma once
#include "Collision.h"
#include "Object3d.h"
#include "Model.h"
#include "Camera.h"
#include "Input.h"
#include "MouseInput.h"
#include "PBullet.h"


class Player
{
public:

	Player(float hp, XMFLOAT2 pos, Object3d* player, ID3D12Device* dev);

	void Initialize();

	void Update(Camera* camera,Input*input);

	void Move(Camera* camera);

	void Roll();

	void Damage(int dmg);

	bool Shot(MouseInput* mouse);

	void Draw();

	bool IsDead();

	float GetHp();

	Object3d GetObjectShape();

	XMFLOAT3 GetPosition();

	XMFLOAT3 GetRotation();

	void Release();

private:
	Input* input;
	MouseInput* mouse;
	XMFLOAT3 position;
	XMFLOAT3 shotdirect;
	XMFLOAT3 feyePos;
	XMFLOAT3 ftargetPos;
	XMFLOAT3 camPos;
	XMFLOAT3 rotate;
	XMFLOAT3 maxRote;
	Object3d* pObj;
	Collision* col;

	float hp;
	bool isDead;
	bool once;
};