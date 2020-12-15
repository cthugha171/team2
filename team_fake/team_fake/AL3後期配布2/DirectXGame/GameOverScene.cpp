#include "GameOverScene.h"
#include "SceneManager.h"
#include "SafeDelete.h"
#include "Vector2.h"

void GameOverScene::Initialize(DirectXCommon* directXInit)
{
	deltaTime = new DeltaTime();
	Sprite::LoadTexture(0, L"");
	Sprite::LoadTexture(1, L"");
	Sprite::LoadTexture(2, L"Resouces/TitilePushKey.png");
	overBG = Sprite::Create(0, { 0,0 });
	overName = Sprite::Create(1, { 50,-70 });
	overPushKey= Sprite::Create(2, { 0,0 });
}

void GameOverScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	if (input->isKeyDown(DIK_SPACE))
	{
		SceneManager::instance().ChangeScene("Title");
	}

	{
		if (colorChange)
		{
			time += deltaTime->deltaTime();
			colorGB = Vector2::lerp(1, 0, time / 3);
			overPushKey->SetColor({ 1,colorGB,colorGB ,1 });
			if (colorGB < 0)
			{
				colorChange = false;
			}
		}

		else if (colorChange == false)
		{
			time += deltaTime->deltaTime();
			colorGB = Vector2::lerp(0, 1, time / 3);
			overPushKey->SetColor({ 1,colorGB,colorGB ,1 });
			if (colorGB >= 1)
			{
				colorChange = true;
			}
		}

		if (time / 3 >= 1)
		{
			time = 0;
		}
	}
}

void GameOverScene::Draw(DirectXCommon* directXInit)
{
	ID3D12GraphicsCommandList* cmdList = directXInit->GetCommandList();

	Sprite::PreDraw(cmdList);

	overBG->Draw();
	overName->Draw();
	overPushKey->Draw();

	Sprite::PostDraw();
}

void GameOverScene::Delete()
{
	safe_delete(overBG);
	safe_delete(overName);
	safe_delete(overPushKey);
}
