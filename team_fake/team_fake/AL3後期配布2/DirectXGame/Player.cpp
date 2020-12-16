#include "Player.h"

Player::Player(float hp, XMFLOAT2 pos, Object3d* player, ID3D12Device* dev)
{
	this->hp = hp;
	position = XMFLOAT3(pos.x, pos.y, 0);
	shotdirect = XMFLOAT3(pos.x, pos.y, 50);
	camPos = XMFLOAT3(0, 0, 0);
	rotate = XMFLOAT3(0, 270, 0);
	maxRote = XMFLOAT3(45.0f, 0, 45.0f);
	pObj = player;
	pObj->SetRotation(rotate);
	pObj->SetScale({ 5,5,5 });
	isDead = false;
	once = false;
}

void Player::Initialize()
{
	col = new Collision();
}

void Player::Update(Camera* camera,Input*input)
{
	if (!once);
	{
		this->input = input;
		once = true;
	}

	camPos = { 0,0,0 };
	if (hp <= 0)
	{
		hp = 0;
		isDead = true;
		return;
	}
	Move();
	Roll();
	camera->cameraMove(camPos);
	pObj->Update(camera->GetmatView(), camera->GetmatProjection());

}

void Player::Move()
{
	if (input->isKeyState(DIK_W))
	{
		//����͖h�~
		if (input->isKeyState(DIK_S))
		{
			goto confirm;
		}
		position.y += 5.0f;
		camPos.y = 5;
	}
	if (input->isKeyState(DIK_S))
	{
		//����͖h�~
		if (input->isKeyState(DIK_W))
		{
			goto confirm;
		}
		position.y -= 5.0f;
		camPos.y = -5;
	}
	if (input->isKeyState(DIK_A))
	{
		//����͖h�~
		if(input->isKeyState(DIK_D))
		{
			goto confirm;
		}
		position.x -= 5.0;
		camPos.x = -5;
	}
	if (input->isKeyState(DIK_D))
	{
		//����͖h�~
		if(input->isKeyState(DIK_A))
		{
			goto confirm;
		}
		position.x += 5.0f;
		camPos.x = 5;
	}

	confirm:
	//position.z += 1.0f;
	//camPos.z = 1.0f;

	pObj->SetPosition(position);
}

void Player::Roll()
{
	if (input->isKeyState(DIK_W))
	{
		rotate.z += 5.0f;
	}
	if (input->isKeyState(DIK_S))
	{
		rotate.z -= 5.0f;
	}
	if (input->isKeyState(DIK_A))
	{
		rotate.x += 5.0f;
	}
	if (input->isKeyState(DIK_D))
	{
		rotate.x -= 5.0f;
	}

	//��]������
	if (rotate.x >= maxRote.x)
	{
		rotate.x = maxRote.x;
	}
	if (rotate.x <= -maxRote.x)
	{
		rotate.x = -maxRote.x;
	}
	if (rotate.z >= maxRote.z)
	{
		rotate.z = maxRote.z;
	}
	if (rotate.z <= -maxRote.z)
	{
		rotate.z = -maxRote.z;
	}

	//���ɖ߂�
	if (rotate.x <= 0)
	{
		rotate.x += 3.0f;
	}
	if (rotate.x >= 0)
	{
		rotate.x -= 3.0f;
	}
	if (rotate.z <= 0)
	{
		rotate.z += 3.0f;
	}
	if (rotate.z >= 0)
	{
		rotate.z -= 3.0f;
	}


	pObj->SetRotation(rotate);
}

void Player::Damage(int dmg)
{
	hp -= dmg;
}

bool Player::Shot(MouseInput* mouse)
{
	return mouse->isLeftDown();
}

void Player::Draw()
{
	pObj->Draw();
}

bool Player::IsDead()
{
	return isDead;
}

float Player::GetHp()
{
	return hp;
}


Object3d Player::GetObjectShape()
{
	return *pObj;
}

XMFLOAT3 Player::GetPosition()
{
	return position;
}

XMFLOAT3 Player::GetRotation()
{
	return rotate;
}

void Player::Release()
{
}
