#include "Enemy.h"
#include <cmath>

Enemy::Enemy()
{
}

void Enemy::Initialize(State state, XMFLOAT3 pos, Object3d* eobj, ID3D12Device* dev)
{
	position = pos;
	eObj = eobj;
	ste = state;
	rotate = { 0,90,0 };
	isDead = false;
	eObj->SetPosition(position);
	eObj->SetRotation(rotate);
	col = new Collision();
	once = false;
	switch (ste)
	{
	case lookat:
		hp = 10;
		break;
	case escape:
		hp = 5;
		break;
	case shot:
		hp = 20;
		break;
	}
}

void Enemy::Update(Camera* camera, Player* player)
{
	if (hp <= 0)
	{
		hp = 0;
		Enemy::~Enemy();
		return;
	}

	switch (ste)
	{
	case lookat://ˆê’è”ÍˆÍ‰ñ“]
		LookUp(player);
		break;
	case escape://“¦‚°‚é
		EscapeUp(player);
		break;
	case shot://UŒ‚‚·‚é
		ShotUp();
		break;
	}

	//eObj->Update(camera->GetmatView(), camera->GetmatProjection());
}

void Enemy::Draw()
{
	if (IsDead())return;
	eObj->Draw();
}

void Enemy::LookUp(Player* player)
{
	if (!once)
	{
		distx = position.x - player->GetPosition().x;
		disty = position.y - player->GetPosition().y;
		distz = position.z - player->GetPosition().z;
		float c = sqrt(distx * distx + disty * disty + distz * distz);
		//³‹K‰»
		float mag = 1 / c;

		distx *= mag;
		disty *= mag;          
		distz *= mag;

		once = true;
	}


}

void Enemy::EscapeUp(Player* player)
{
	//Object3d* shape = &other->GetObjectShape();
	//XMFLOAT3 pos1 = eObj->GetPosition();
	//XMFLOAT3 pos2 = shape->GetPosition();
	////float r1 = eObj->GetRadius() * 5;
	////float r2 = shape->GetRadius();

	//float x = powf(pos2.x - pos1.x, 2);
	//float y = powf(pos2.y - pos1.y, 2);
	//float z = powf(pos2.z - pos2.z, 2);
	//float r = powf(r1 + r2, 2);
	//if (x + y + z <= r)
	//{
	//	position.x -= 5.0;
	//	position.z += 5.0;

	//	rotate.y += 1;
	//}
	//eObj->SetPosition(position);
	//eObj->SetRotation(rotate);
}

void Enemy::ShotUp()
{
}

void Enemy::Damage(int dmg)
{
	hp -= dmg;
}

bool Enemy::Collisions(Player* player)
{
	return col->SphereToSphere(eObj, &player->GetObjectShape());
}

bool Enemy::Shot()
{
	return false;
}

bool Enemy::IsDead()
{
	return isDead;
}

float Enemy::GetHp()
{
	return hp;
}

Object3d Enemy::GetObjectShape()
{
	return *eObj;
}

XMFLOAT3 Enemy::GetPosition()
{
	return position;
}

void Enemy::Release()
{
}
