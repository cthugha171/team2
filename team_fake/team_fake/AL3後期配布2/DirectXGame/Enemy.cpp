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
	eObj->SetRadius(10);
	col = new Collision();
	once = false;
	addx = 0;
	addy = 0;
	switch (ste)
	{
	case lookat:
		hp = 10;
		speed = 2.0f;
		break;
	case escape:
		hp = 5;
		speed = 1.0f;
		break;
	case shots:
		hp = 20;
		speed = 1.5f;
		break;
	}
}

void Enemy::Update(Camera* camera, Player* player)
{
	if (hp <= 0)
	{
		hp = 0;
		isDead = true;
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
	case shots://UŒ‚‚·‚é
		ShotUp();
		break;
	}

	eObj->Update(camera->GetmatView(), camera->GetmatProjection());
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
		float c = sqrt(distx * distx + disty * disty);
		//³‹K‰»
		float mag = 1 / c;

		distx *= mag;
		disty *= mag;

		once = true;
	}

	float rad_xy = atan2(distx, disty);

	position.x -= cos(rad_xy) * speed;
	position.y -= sin(rad_xy) * speed;
	position.z -= speed;

	eObj->SetPosition(position);
	if (Collisions(player))
	{
		hp = 0;
	}

}

void Enemy::EscapeUp(Player* player)
{
	float x = position.x - player->GetPosition().x;
	float y = position.y - player->GetPosition().y;

	if (x >= 0)
	{
		if(addx>=25)
		{
			goto confirm;
		}
		position.x += speed;
		addx++;
	}
	else if (x < 0)
	{
		if (addx <= -25)
		{
			goto confirm;
		}
		position.x -= speed;
		addx--;
	}

	if (y >= 0)
	{
		if (addy >= 25)
		{
			goto confirm;
		}
		position.y += speed;
		addy++;
	}
	else if (y < 0)
	{
		if (addx <= -25)
		{
			goto confirm;
		}
		position.y -= speed;
		addy--;
	}

	confirm:

	eObj->SetPosition(position);
	eObj->SetRotation(rotate);
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
