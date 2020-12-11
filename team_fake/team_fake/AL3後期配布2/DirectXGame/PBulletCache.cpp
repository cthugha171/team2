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
	//キャッシュがあるかどうか、あれば使用
	if (cache.size() > 0)
	{
		//front関数を使用しキュー先端のオブジェクトを取得
		auto pbullet = cache.front();
		//初期化処理
		pbullet->Initialize(pos,bullet);
		//キューをポップする
		cache.pop();
		return pbullet;
	}
	
	//インスタンスを生成
	auto pbullet = new PBullet();

	//初期化処理
	pbullet->Initialize(pos, bullet);

	return pbullet;
}

void PBulletCache::Cache(PBullet* pbullet)
{
	pbullet->SetBoolShot(false);

	cache.push(pbullet);
}
