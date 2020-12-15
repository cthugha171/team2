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
	void Update(Player* player, MouseInput* mouse, Camera* camera, WinApp* winApp);

	void Draw();

	std::list<PBullet*> shotList;
private:
	PBulletCache cache;
	int max = 0;
};