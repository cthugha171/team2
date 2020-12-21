#pragma once
#include "IScene.h"
#include "Sprite.h"
#include "DirectXCommon.h"//#include "DirecXInit.h"
#include "Input.h"
#include "Model.h"
#include "Object3d.h"
#include "DeltaTime.h"
#include "Audio.h"

class TitleScene : public IScene
{
public:
	void Initialize(DirectXCommon* directXInit);

	void Update(Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp);

	void Draw(DirectXCommon* directXInit);

	void Delete();
private:
	Sprite* TitleBG=nullptr;
	Sprite* TitleName = nullptr;
	Sprite* TitlePushKey = nullptr;
	DeltaTime* deltaTime;
	float time=0;
	float colorGB = 0;

	Object3d* player;
	Model* pModel;
	bool colorChange = true;
	Audio* bgm;
	bool sceneChange = false;
};
