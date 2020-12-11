#pragma once
#include "Enemy.h"
#include<queue>
#include<list>

class EnemyCache
{
public:
	~EnemyCache();

	Enemy* Instance(State state, XMFLOAT3 pos, Object3d* eobj, ID3D12Device* dev);

	void Cache(Enemy* enemy);

private:
	std::queue<Enemy*>cache;

};

class EnemySpawner
{
public:
	~EnemySpawner();

	void spawn(State state, XMFLOAT3 pos, Object3d* eobj, ID3D12Device* dev);

	void Update(Camera* camera, Player* other);

	void Draw(ID3D12GraphicsCommandList* cmdList);

private:
	std::list<Enemy*>enemyList;
	EnemyCache cache;
};

