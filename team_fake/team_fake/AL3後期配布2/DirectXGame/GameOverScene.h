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
	Sprite* overPushKey = nullptr;
	Sprite* G = nullptr;
	Sprite* A = nullptr;
	Sprite* M = nullptr;
	Sprite* E = nullptr;
	Sprite* O = nullptr;
	Sprite* V = nullptr;
	Sprite* E2 = nullptr;
	Sprite* R = nullptr;
	DeltaTime* deltaTime;
	float dTime = 0;
	float time = 0;
	float time2 = 0;
	float time3 = 0;
	float colorGB = 0;
	float gx = 0, gy = 0;
	float ax = 0, ay = 0;
	float mx = 0, my = 0;
	float ex = 0, ey = 0;
	float ox = 0, oy = 0;
	float vx = 0, vy = 0;
	float e2x = 0, e2y = 0;
	float rx = 0, ry = 0;

	bool colorChange = true;
	bool sceneChange = false;
	bool Cbgm;
	Audio* se;
	Audio* bgm;

};

