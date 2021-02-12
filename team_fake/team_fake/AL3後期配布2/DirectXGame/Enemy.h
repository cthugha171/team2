#pragma once
#include "Player.h"
#include "Collision.h"
#include "Object3d.h"
#include "Model.h"
#include "Camera.h"

enum State //enemy�s���p�^�[���ω��p
{
	lookat,//���͈̔͂��ړ�
	escape,//�v���C���[���瓦����
	shots,//�U������
};

class Player;

class Enemy
{
public:
	Enemy();

	void Initialize(State state, XMFLOAT3 pos, Object3d* eobj,Model*dyingModel, ID3D12Device* dev);

	void Update(Camera* camera, Player* player);

	void Draw();

	void LookUp(Player* player);

	void EscapeUp(Player* player);

	void ShotUp();

	void Damage(int dmg);

	bool Collisions(Player* player);

	bool Shot();

	bool IsDead();

	bool IsDying();

	void Dying();

	float GetHp();

	Object3d* GetObjectShape();

	XMFLOAT3 GetPosition();

	void Release();

private:
	XMFLOAT3 position;
	XMFLOAT3 plPos;
	XMFLOAT3 rotate;
	XMFLOAT3 dyingSize;
	Model* dyingModel;
	Object3d* eObj;
	Collision* col;

	State ste;

	float hp;
	float distx;
	float disty;
	float speed;
	float addx;
	float addy;

	bool isDead;
	bool isDying;
	bool once;
};