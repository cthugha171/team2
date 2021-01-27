#pragma once
#pragma once
#include "IScene.h"
#include "Sprite.h"
#include "DirectXCommon.h"//#include "DirecXInit.h"
#include "Input.h"
#include "Model.h"
#include "Object3d.h"
#include "DeltaTime.h"
#include "Audio.h"

class GameOverScene:public IScene
{
public:
	void Initialize(DirectXCommon* directXInit);

	void Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp);

	void Draw(DirectXCommon* directXInit);

	void Delete();

private:
	Sprite* GameOverBG = nullptr;
	Sprite* G = nullptr;
	Sprite* A = nullptr;
	Sprite* M = nullptr;
	Sprite* E = nullptr;
	Sprite* O = nullptr;
	Sprite* V = nullptr;
	Sprite* E2 = nullptr;
	Sprite* R = nullptr;
	DeltaTime* deltaTime;
	float time = 0;
	float colorGB = 0;

	bool colorChange = true;
	bool sceneChange = false;
	Audio* bgm;

};

