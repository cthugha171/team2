#include "Enemy.h"
#include <cmath>

Enemy::Enemy()
{
}

void Enemy::Initialize(State state, XMFLOAT3 pos, Object3d* eobj,Model* dyingModel, ID3D12Device* dev)
{
	position = pos;
	eObj = eobj;
	ste = state;
	rotate = { 0,90,0 };
	dyingSize = { 1,1,1 };
	isDead = false;
	isDying = false;
	eObj->SetPosition(position);
	eObj->SetRotation(rotate);
	eObj->SetRadius(10);
	this->dyingModel = dyingModel;
	col = new Collision();
	once = false;
	addx = 0;
	addy = 0;
	switch (ste)
	{
	case lookat:
		hp = 10;
		speed = 0.5f;
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
	if (hp <= 0&&!isDying)
	{
		hp = 0;
		isDying = true;
		eObj->SetModel(dyingModel);
		eObj->SetScale(dyingSize);
	}

	if (isDying)
	{
		Dying();
		return;
	}

	switch (ste)
	{
	case lookat://àÍíËîÕàÕâÒì]
		LookUp(player);
		break;
	case escape://ì¶Ç∞ÇÈ
		EscapeUp(player);
		break;
	case shots://çUåÇÇ∑ÇÈ
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
		//ê≥ãKâª
		float mag = 1 / c;

		distx *= mag;
		disty *= mag;

		once = true;
	}

	float rad_xy = atan2(distx, disty);

	position.x += cos(rad_xy) * speed;
	position.y += sin(rad_xy) * speed;
	position.z -= speed;

	if (position.y <= 10)
	{
		position.y = 10;
	}

	eObj->SetPosition(position);
}

void Enemy::EscapeUp(Player* player)
{
	float x = position.x - player->GetPosition().x;
	float y = position.y - player->GetPosition().y;

	if (x >= 0)
	{
		if(addx>=100)
		{
			goto confirm;
		}
		position.x += speed;
		addx++;
	}
	else if (x < 0)
	{
		if (addx <= -100)
		{
			goto confirm;
		}
		position.x -= speed;
		addx--;
	}

	if (y >= 0)
	{
		if (addy >= 100)
		{
			goto confirm;
		}
		position.y += speed;
		addy++;
	}
	else if (y < 0)
	{
		if (addx <= 10)
		{
			goto confirm;
		}
		position.y -= speed;
		addy--;
	}

	confirm:

	if (position.y <= 10)
	{
		position.y = 10;
	}

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

bool Enemy::IsDying()
{
	return isDying;
}

void Enemy::Dying()
{
	if (eObj->GetScale().x <= 100)
	{
		dyingSize.x += 5;
		dyingSize.y += 5;
		dyingSize.z += 5;

		eObj->SetScale(dyingSize);
	}
	else
	{
		isDead = true;
	}

}

float Enemy::GetHp()
{
	return hp;
}

Object3d* Enemy::GetObjectShape()
{
	return eObj;
}

XMFLOAT3 Enemy::GetPosition()
{
	return position;
}

void Enemy::Release()
{
}
