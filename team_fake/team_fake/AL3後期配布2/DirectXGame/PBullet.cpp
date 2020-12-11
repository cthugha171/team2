#include "PBullet.h"
#include <cmath>


void PBullet::Initialize(XMFLOAT3 pos, Object3d* bullet)
{
	position = pos;
	pbObj = bullet;
	speed = 10;
	col = new Collision();
	distX = 0;
	distY = 0;
	shot = true;
	once = false;
}

void PBullet::Update(Enemy* enemy,Player*player,MouseInput* mouse,Camera*camera,WinApp*winApp)
{
	if (!shot)
	{
		return;
	}
	Move(player, mouse, camera, winApp);
	//pbObj->Update(camera->GetmatView(), camera->GetmatProjection());
}

void PBullet::Move(Player* player, MouseInput* mouse,Camera*camera,WinApp*winApp)
{
	if (!once)
	{
		//distX = mouse->GetMousePos(*camera, winApp).x - player->GetPosition().x;
		//distY = mouse->GetMousePos(*camera, winApp).y - player->GetPosition().y;
		//float c = std::hypot(distX, distY);
		////³‹K‰»
		//float mag = 1 / c;

		//distX *= mag;
		//distY *= mag;            

		once = true;
	}

	/*float radian = atan2(distY, distX);
	
	position.x += cos(radian) * speed;
	position.y += sin(radian) * speed;*/

	position.z += speed;

	pbObj->SetPosition(position);
}

void PBullet::Draw()
{
	if(!shot)
	{
		return;
	}
	pbObj->Draw();
}

void PBullet::SetBoolShot(bool value)
{
	shot = value;
}

bool PBullet::Collisions(Enemy* other)
{
	return col->SphereToSphere(pbObj, &other->GetObjectShape());
}

Object3d PBullet::GetObjectShape()
{
	return *pbObj;
}

XMFLOAT3 PBullet::GetPosition()
{
	return position;
}

void PBullet::Release()
{
}
