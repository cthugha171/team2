#include"SceneManager.h"
#include <memory>

//�C���X�^���X
SceneManager& SceneManager::instance()
{
	static unique_ptr<SceneManager>instance(new SceneManager);
	return *instance;
}

//�V�[���ǉ�
void SceneManager::Add(string name, IScene* scene)
{
	if (scenes.count(name))
	{
		return;
	}
	scenes[name] = scene;
}

//�J�n�̃V�[��
void SceneManager::StartScene(string name)
{
	if (!scenes.count(name))
	{
		return;
	}
	currentScene = scenes[name];
	state = SceneState::Initialize;
}

//�V�[���ύX
void SceneManager::ChangeScene(string name)
{
	if (!scenes.count(name))
		return;

	nextScene = scenes[name];
	state = SceneState::Delete;

}

void SceneManager::update(DirectXCommon* directXInit,Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	if (currentScene == nullptr)
	{
		return;
	}

	if (state == SceneState::Initialize)
	{
		currentScene->Initialize(directXInit);
		state = SceneState::Updata;
	}

	if (state == SceneState::Delete)
	{
		currentScene->Delete();
		NextScene();
	}

	if (state == SceneState::Updata)
	{
		currentScene->Update(input,mouse,camera,winApp);

		currentScene->Draw();
	}
}

//	���̃V�[���ɐ؂�ւ���
void SceneManager::NextScene()
{
	state = SceneState::Initialize;
	currentScene = nextScene;
}

