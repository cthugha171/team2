#pragma once
#include<list>
#include"PBullet.h"
#include"PBulletCache.h"

class PlayerShot
{
public:
	//�f�X�g���N�^
	~PlayerShot();

	//�e��ł�
	void Shot(const XMFLOAT3& pos, Object3d* bullet);

	//�X�V
	void Update(Enemy* enemy, Player* player, MouseInput* mouse, Camera* camera, WinApp* winApp);

	void Draw();
private:
	std::list<PBullet*> shotList;
	PBulletCache cache;
};