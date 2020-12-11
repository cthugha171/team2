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
#include "PlayerShot.h"
//#include "UI.h"
#include "DeltaTime.h"

#include "SafeDelete.h"
class GameScene :public IScene
{
public:
	void Initialize(DirectXCommon* directXInit);
	void Update(Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp);
	void Draw();
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
	Object3d* object3d2;
	Object3d* pObj;
	Object3d* eObj;
	Object3d* pbObj;
	Player* player;
	Enemy* enemy;
	PlayerShot playerShot;
	//UI* ui;

	DeltaTime* deltaTime;

	bool oto = false;
	float time = 0;
};
