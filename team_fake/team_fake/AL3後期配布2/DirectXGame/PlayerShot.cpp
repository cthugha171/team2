#include "PlayerShot.h"

PlayerShot::~PlayerShot()
{
	for (auto shot : shotList)
	{
		delete shot;
	}
}

void PlayerShot::Shot(const XMFLOAT3& pos, Object3d* bullet)
{
	//弾の生成,初期化
	PBullet* shot = cache.Instance(pos, bullet);
	//弾のリストに格納
	shotList.push_back(shot);
}

void PlayerShot::Update(Enemy* enemy, Player* player, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	for (auto it = shotList.begin();it != shotList.end();)
	{
		(*it)->Update(enemy, player, mouse, camera, winApp);
		if ((*it)->Collisions(enemy))
		{
			enemy->Damage(10);
		}

		//弾が画面外なら
		if ((*it)->GetPosition().x - camera->getEyePos().x < -winApp->GetWindowWidthSize() || (*it)->GetPosition().y - camera->getEyePos().y < -winApp->GetWindowHeightSize() || (*it)->GetPosition().z - camera->getEyePos().z < -500 ||
			(*it)->GetPosition().x - camera->getEyePos().x > winApp->GetWindowWidthSize() || (*it)->GetPosition().y - camera->getEyePos().y > winApp->GetWindowHeightSize() || (*it)->GetPosition().z - camera->getEyePos().z > 500)
		{
			cache.Cache(*it);
			it = shotList.erase(it);
			continue;
		}
		++it;
	}
}

void PlayerShot::Draw()
{
	for (auto shot : shotList)
	{
		shot->Draw();
	}
}
