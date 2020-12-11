#pragma once
#include "IScene.h"
#include <map>
#include <d3dx12.h>
#include "DirectXCommon.h"//#include "DirecXInit.h"
#include "Input.h"
#include "MouseInput.h"
#include "Camera.h"

using namespace std;

enum SceneState {
	Initialize,
	Updata,
	Draw,
	Delete
};

class SceneManager
{
public:
	static SceneManager& instance();
	//シーンの追加
	void Add(string name, IScene* scene);

	//開始シーンを設定
	void StartScene(string name);

	//シーン変更
	void ChangeScene(string name);

	//シーン更新
	void update(DirectXCommon* directXInit,Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp);

private:
	void NextScene();

private:
	//シーン管理用map
	map<string, IScene*> scenes;
	//現在のシーン
	IScene* currentScene;
	//次のシーン
	IScene* nextScene;
	//シーンの状態
	SceneState state;
};
