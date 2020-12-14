#pragma once
#include "Player.h"
#include "Collision.h"
#include "Object3d.h"
#include "Model.h"
#include "Camera.h"

enum State //enemy行動パターン変化用
{
	lookat,//一定の範囲を移動
	escape,//プレイヤーから逃げる
	shot,//攻撃する
};

class Player;

class Enemy
{
public:
	Enemy();

	void Initialize(State state, XMFLOAT3 pos, Object3d* eobj, ID3D12Device* dev);

	void Update(Camera* camera, Player* player);

	void Draw();

	void LookUp(Player* player);

	void EscapeUp(Player* player);

	void ShotUp();

	void Damage(int dmg);

	bool Collisions(Player* player);

	bool Shot();

	bool IsDead();

	float GetHp();

	Object3d GetObjectShape();

	XMFLOAT3 GetPosition();

	void Release();

private:
	XMFLOAT3 position;
	XMFLOAT3 plPos;
	XMFLOAT3 rotate;
	Object3d* eObj;
	Collision* col;

	State ste;

	float hp;
	float distx;
	float disty;
	float speed;

	bool isDead;
	bool once;
};