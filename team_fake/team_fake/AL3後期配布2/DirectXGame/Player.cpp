#include "Player.h"

Player::Player(float hp, XMFLOAT2 pos, Object3d* player, ID3D12Device* dev)
{
	this->hp = hp;
	position = XMFLOAT3(pos.x, pos.y, 0);
	shotdirect = XMFLOAT3(pos.x, pos.y, 50);
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
		feyePos = camera->getEyePos();
		ftargetPos = camera->getTargetPos();
		once = true;
	}

	if (hp <= 0)
	{
		hp = 0;
		isDead = true;
		return;
	}
	Move(camera);
	Roll();
	pObj->Update(camera->GetmatView(), camera->GetmatProjection());

}

void Player::Move(Camera* camera)
{
	if (input->isKeyState(DIK_W))
	{
		//Œë“ü—Í–hŽ~
		if (input->isKeyState(DIK_S))
		{
			goto confirm;
		}
		position.y += 5.0f;
		feyePos.y += 5;
		ftargetPos.y += 5;
	}
	if (input->isKeyState(DIK_S))
	{
		//Œë“ü—Í–hŽ~
		if (input->isKeyState(DIK_W))
		{
			goto confirm;
		}
		position.y -= 5.0f;
		feyePos.y -= 5;
		ftargetPos.y -= 5;
	}
	if (input->isKeyState(DIK_A))
	{
		//Œë“ü—Í–hŽ~
		if(input->isKeyState(DIK_D))
		{
			goto confirm;
		}
		position.x -= 5.0;
		feyePos.x -= 5;
		ftargetPos.x -= 5;
	}
	if (input->isKeyState(DIK_D))
	{
		//Œë“ü—Í–hŽ~
		if(input->isKeyState(DIK_A))
		{
			goto confirm;
		}
		position.x += 5.0f;
		feyePos.x += 5;
		ftargetPos.x += 5;
	}

confirm:

	if (feyePos.x >= position.x )
	{
		feyePos.x -= 0.5;
	}
	if (feyePos.x <= position.x)
	{
		feyePos.x += 0.5;
	}
	if (feyePos.y >= position.y )
	{
		feyePos.y -= 0.5;
	}
	if (feyePos.y <= position.y)
	{
		feyePos.y += 0.5;
	}
	if (ftargetPos.x >= position.x )
	{
		ftargetPos.x -= 0.5;
	}
	if (ftargetPos.x <= position.x)
	{
		ftargetPos.x += 0.5;
	}
	if (ftargetPos.y >= position.y )
	{
		ftargetPos.y -= 0.5;
	}
	if (ftargetPos.y <= position.y)
	{
		ftargetPos.y += 0.5;
	}

	if (position.y <= 0)
	{
		position.y = 0;
		feyePos.y = 0;
		ftargetPos.y = 0;
		camera->setEyePos(feyePos);
		camera->setTargetPos(ftargetPos);
		Damage(1);
	}

	camera->setEyePos(feyePos);
	camera->setTargetPos(ftargetPos);

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

	//‰ñ“]‚·‚éãŒÀ
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

	//Œ³‚É–ß‚·
	if (rotate.x < 0)
	{
		rotate.x += 3.0f;
	}
	if (rotate.x > -0)
	{
		rotate.x -= 3.0f;
	}
	if (rotate.z < -0)
	{
		rotate.z += 3.0f;
	}
	if (rotate.z > 0)
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
