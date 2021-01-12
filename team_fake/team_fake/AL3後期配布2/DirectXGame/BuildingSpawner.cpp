#include "BuildingSpawner.h"


BuildingCache::~BuildingCache()
{
	while (!cache.empty())
	{
		auto  build = cache.front();
		delete build;
		cache.pop();
	}
}

Building* BuildingCache::Instance(state state,XMFLOAT2 pos, Object3d* obj, Object3d* obj2)
{
	if (cache.size() > 0)
	{
		auto build = cache.front();

		build->Initialize(state,pos, obj,obj2);

		cache.pop();

		return build;
	}

	auto build = new Building();

	build->Initialize(state,pos,obj,obj2);

	return build;
}

void BuildingCache::Cache(Building* building)
{
	cache.push(building);
}

BuildingSpawner::~BuildingSpawner()
{
	for (auto build : BuildingList)
	{
		delete build;
	}
}

void BuildingSpawner::Spawn(XMFLOAT2 pos, Object3d* obj, Object3d* obj2)
{
	if(changestate==0)
	{
		sta = low;
		changestate=1;
		goto confirm;
	}
	if (changestate == 1)
	{
		sta = high;
		changestate = 2;
		goto confirm;
	}
	if(changestate==2)
	{
		sta == mid;
		changestate = 0;
		goto confirm;
	}

confirm:

	Building* build = cache.Instance(sta,pos, obj,obj2);

	BuildingList.push_back(build);
}

void BuildingSpawner::Update(Camera* camera)
{
	for (auto it = BuildingList.begin(); it != BuildingList.end();)
	{
		(*it)->Update(camera);
		if ((*it)->GetPosition().z <= -50)
		{
			cache.Cache(*it);
			it = BuildingList.erase(it);
			continue;
		}
		it++; 
	}
}

void BuildingSpawner::Draw()
{
	for (auto build : BuildingList)
	{
		build->Draw();
	}
}
