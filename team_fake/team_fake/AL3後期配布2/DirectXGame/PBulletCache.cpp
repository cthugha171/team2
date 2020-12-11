#include "PBulletCache.h"

PBulletCache::~PBulletCache()
{
	while (!cache.empty())
	{
		auto pbullet = cache.front();
		delete pbullet;
		cache.pop();
	}
}

PBullet* PBulletCache::Instance(XMFLOAT3 pos, Object3d* bullet)
{
	//�L���b�V�������邩�ǂ����A����Ύg�p
	if (cache.size() > 0)
	{
		//front�֐����g�p���L���[��[�̃I�u�W�F�N�g���擾
		auto pbullet = cache.front();
		//����������
		pbullet->Initialize(pos,bullet);
		//�L���[���|�b�v����
		cache.pop();
		return pbullet;
	}
	
	//�C���X�^���X�𐶐�
	auto pbullet = new PBullet();

	//����������
	pbullet->Initialize(pos, bullet);

	return pbullet;
}

void PBulletCache::Cache(PBullet* pbullet)
{
	pbullet->SetBoolShot(false);

	cache.push(pbullet);
}
