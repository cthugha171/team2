#include "TitleScene.h"
#include "SceneManager.h"

void TitleScene::Initialize(DirectXCommon* directXInit)
{
	//sprite[0].initialize(directXInit->GetDev(), L"Resources/TITLE.png", 50, 50);

	//ƒ‚ƒfƒ‹
}

void TitleScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	if (input->isKeyDown(DIK_ESCAPE))
	{
		SceneManager::instance().ChangeScene("Game");
	}

}

void TitleScene::Draw(DirectXCommon* directXInit)
{
	//sprite[0].update({ 50,50 }, directXInit->GetDev(), directXInit->GetcmdList());
}

void TitleScene::Delete()
{
}
