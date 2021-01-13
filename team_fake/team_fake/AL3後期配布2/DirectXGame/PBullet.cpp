#include "PBullet.h"
#include "Sprite.h"
#include <cmath>


void PBullet::Initialize(XMFLOAT3 pos, Object3d* bullet)
{
	position = XMFLOAT3(pos.x,pos.y,10);
	pbObj = bullet;
	pbObj->SetRadius(1.0f);
	pbObj->SetScale({ 2,2,2 });
	speed = 5;
	col = new Collision();
	dist = Vector3(0,0,0);
	distX = 0;
	distZ = 0;
	shot = true;
	once = false;
}

void PBullet::Update(Player*player,MouseInput* mouse,Camera*camera,WinApp*winApp)
{
	if (!shot)
	{
		return;
	}
	Move(player, mouse, camera, winApp);
	pbObj->Update(camera->GetmatView(), camera->GetmatProjection());
}

void PBullet::Move(Player* player, MouseInput* mouse,Camera*camera,WinApp*winApp)
{
	if (!once)
	{
		//distX = mouse->GetMousePos(*camera, winApp).x - player->GetPosition().x;
		//distY = mouse->GetMousePos(*camera, winApp).y - player->GetPosition().y;

		dist.x = player->GetRotation().x;
		dist.z = player->GetRotation().z;

		//³‹K‰»
		dist = dist.normalize();

		once = true;
	}


	float radian = atan2(dist.z, dist.x);
	
	position.x += cos(radian) * speed*0.5f;
	position.y += sin(radian) * speed*0.5f;

	/*position.x += distX * speed;
	position.y += distY * speed;*/

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
	return col->SphereToSphere(pbObj, other->GetObjectShape());
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
