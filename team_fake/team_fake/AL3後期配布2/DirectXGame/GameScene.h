#pragma once
#include "IScene.h"
#include "Sprite.h"
#include "Audio.h"
#include "Sprite.h"
#include "DirectXCommon.h"//#include "DirecXInit.h"
#include "Model.h"
#include "Object3d.h"
#include "Player.h"
#include "Enemy.h"
#include "CreateEnemyObject.h"
#include "CreateBulletObj.h"
#include "PlayerShot.h"
#include "EnemySpawner.h"
#include "UI.h"
#include "DeltaTime.h"

#include "SafeDelete.h"
class GameScene :public IScene
{
public:
	void Initialize(DirectXCommon* directXInit);
	void Update(Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp);
	void Draw(DirectXCommon* directXinit);
	void Delete();

private:
	DirectXCommon* directXinit;
	Audio* audio;
	Model* ground;
	Model* model;
	Model* pModel;
	Model* eModel;
	Model* pbModel;
	Object3d* objground;
	Object3d* pObj;
	Object3d* eObj;
	Object3d* pbObj;
	Player* player;
	Enemy* enemy;
	CreateEnemyObject eneObj;
	CreateBulletObj bobj;
	PlayerShot playerShot;
	EnemySpawner eneSpawn;
	UI* ui;

	DeltaTime* deltaTime;
	
	XMFLOAT3 epos;

	bool oto = false;
	float time = 0;
	float time2 = 0;
};
