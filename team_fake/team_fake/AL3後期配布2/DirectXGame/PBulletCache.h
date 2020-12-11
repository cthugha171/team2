#pragma once
#include <queue>
#include"PBullet.h"

class PBulletCache
{
public:
	//デストラクタ
	~PBulletCache();

	//弾を生成する、キャッシュがあればそれを使用
	PBullet* Instance(XMFLOAT3 pos, Object3d* bullet);

	//弾のキャッシュ作成
	void Cache(PBullet* pbullet);
private:
	std::queue<PBullet*> cache;
};