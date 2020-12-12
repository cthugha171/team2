#include"SceneManager.h"
#include <memory>

//インスタンス
SceneManager& SceneManager::instance()
{
	static unique_ptr<SceneManager>instance(new SceneManager);
	return *instance;
}

//シーン追加
void SceneManager::Add(string name, IScene* scene)
{
	if (scenes.count(name))
	{
		return;
	}
	scenes[name] = scene;
}

//開始のシーン
void SceneManager::StartScene(string name)
{
	if (!scenes.count(name))
	{
		return;
	}
	currentScene = scenes[name];
	state = SceneState::Initialize;
}

//シーン変更
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

		currentScene->Draw(directXInit);
	}
}

//	次のシーンに切り替える
void SceneManager::NextScene()
{
	state = SceneState::Initialize;
	currentScene = nextScene;
}

