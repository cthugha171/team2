#pragma once
#include <queue>
#include"PBullet.h"

class PBulletCache
{
public:
	//�f�X�g���N�^
	~PBulletCache();

	//�e�𐶐�����A�L���b�V��������΂�����g�p
	PBullet* Instance(XMFLOAT3 pos, Object3d* bullet);

	//�e�̃L���b�V���쐬
	void Cache(PBullet* pbullet);
private:
	std::queue<PBullet*> cache;
};