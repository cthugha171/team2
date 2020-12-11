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
	//�V�[���̒ǉ�
	void Add(string name, IScene* scene);

	//�J�n�V�[����ݒ�
	void StartScene(string name);

	//�V�[���ύX
	void ChangeScene(string name);

	//�V�[���X�V
	void update(DirectXCommon* directXInit,Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp);

private:
	void NextScene();

private:
	//�V�[���Ǘ��pmap
	map<string, IScene*> scenes;
	//���݂̃V�[��
	IScene* currentScene;
	//���̃V�[��
	IScene* nextScene;
	//�V�[���̏��
	SceneState state;
};
