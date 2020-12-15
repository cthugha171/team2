#include "EnemySpawner.h"


EnemyCache::~EnemyCache()
{
	while (!cache.empty())
	{
		auto enemy = cache.front();
		delete enemy;
		cache.pop();
	}
}


Enemy* EnemyCache::Instance(State state, XMFLOAT3 pos, Object3d* eobj, ID3D12Device* dev)
{
	if (cache.size() > 0)
	{
		auto enemy = cache.front();

		enemy->Initialize(state, pos, eobj, dev);

		cache.pop();

		return enemy;
	}

	auto enemy = new Enemy();

	enemy->Initialize(state, pos, eobj, dev);

	return enemy;
}

void EnemyCache::Cache(Enemy* enemy)
{
	if (enemy->IsDead())
	{
		cache.push(enemy);
	}
}



EnemySpawner::~EnemySpawner()
{
	for (auto enemy : enemyList)
	{
		delete enemy;
	}
}

void EnemySpawner::spawn(XMFLOAT3 pos, Object3d* eobj, ID3D12Device* dev)
{
	if (changestate <= 1)
	{
		ste = escape;
		changestate++;
	}
	else if (changestate >= 2)
	{
		ste = lookat;
		changestate = 0;
	}

	Enemy* enemy = cache.Instance(ste, pos, eobj, dev);

	enemyList.push_back(enemy);
}

void EnemySpawner::Update(Camera* camera, Player* other)
{
	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(camera, other);
		if ((*it)->Collisions(other))
		{
			(*it)->Damage(10);
		}

		if ((*it)->GetHp() < 0)
		{
			cache.Cache(*it);
			it = enemyList.erase(it);
			end++;
			continue;
		}
		it++;
	}
}

void EnemySpawner::Draw()
{
	for (auto enemys : enemyList)
	{
		enemys->Draw();
	}
}

Enemy* EnemySpawner::GetEnemy()
{
	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		return *it;
		it++;
		continue;
	}
}

int EnemySpawner::GetEndFlag()
{
	return end;
}
