#pragma once
#include<list>
#include"PBullet.h"
#include"PBulletCache.h"

class PlayerShot
{
public:
	//デストラクタ
	~PlayerShot();

	//弾を打つ
	void Shot(const XMFLOAT3& pos, Object3d* bullet);

	//更新
	void Update(Enemy* enemy, Player* player, MouseInput* mouse, Camera* camera, WinApp* winApp);

	void Draw();
private:
	std::list<PBullet*> shotList;
	PBulletCache cache;
};