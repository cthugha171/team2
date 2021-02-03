#pragma once
#include "Building.h"
#include<queue>
#include<list>
#include <DirectXMath.h>

using namespace DirectX;

class BuildingCache 
{
public:
	~BuildingCache();

	Building* Instance(state state,XMFLOAT2 pos,XMFLOAT3 dist, Object3d* obj, Object3d* obj2);

	void Cache(Building* building);

private:
	std::queue<Building*>cache;
};

class BuildingSpawner
{
public:
	BuildingSpawner();

	~BuildingSpawner();

	void Spawn(XMFLOAT2 pos,XMFLOAT3 dist, Object3d* obj, Object3d* obj2);

	void Update(Camera* camera);

	void Draw();

	std::list<Building*>BuildingList;

private:
	BuildingCache cache;
	state sta;

	int changestate = 0;
};

