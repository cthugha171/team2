#include "GameOverScene.h"
#include "SceneManager.h"
#include "SafeDelete.h"
#include "Vector2.h"

void GameOverScene::Initialize(DirectXCommon* directXInit)
{
	deltaTime = new DeltaTime();
	time = 0;
	Sprite::LoadTexture(8, L"Resources/GameOverBG.png");
	Sprite::LoadTexture(0, L"Resources/G.png");
	Sprite::LoadTexture(1, L"Resources/A.png");
	Sprite::LoadTexture(2, L"Resources/M.png");
	Sprite::LoadTexture(3, L"Resources/E.png");
	Sprite::LoadTexture(4, L"Resources/O.png");
	Sprite::LoadTexture(5, L"Resources/V.png");
	Sprite::LoadTexture(6, L"Resources/E2.png");
	Sprite::LoadTexture(7, L"Resources/R.png");
	GameOverBG = Sprite::Create(8, { 0,0 });
	G = Sprite::Create(0, { 0,0 });
	//G->SetSize(XMFLOAT2(1000, 1000));
	A = Sprite::Create(1, { 0,0 });
	M = Sprite::Create(2, { 0,0 });
	E = Sprite::Create(3, { 0,0 });
	O = Sprite::Create(4, { 0,0 });
	V = Sprite::Create(5, { 0,0 });
	E2 = Sprite::Create(6, { 0,0 });
	R = Sprite::Create(7, { 0,0 });
}

void GameOverScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	if (input->isKeyDown(DIK_SPACE))
	{
		bgm->PlayWave("Resources/kettei-02.wav");
		sceneChange = true;
	}

	if (sceneChange)
	{
		if (bgm->endAudioCheck())
		{
			SceneManager::instance().ChangeScene("Title");
		}
	}
	

	////“_–Å—p
	//{
	//	if (colorChange)
	//	{
	//		time += deltaTime->deltaTime();
	//		colorGB = Vector2::lerp(1, 0, time / 3);
	//		overPushKey->SetColor({ 1,colorGB,colorGB ,1 });
	//		if (colorGB < 0)
	//		{
	//			colorChange = false;
	//		}
	//	}

	//	else if (colorChange == false)
	//	{
	//		time += deltaTime->deltaTime();
	//		colorGB = Vector2::lerp(0, 1, time / 3);
	//		overPushKey->SetColor({ 1,colorGB,colorGB ,1 });
	//		if (colorGB >= 1)
	//		{
	//			colorChange = true;
	//		}
	//	}

	//	if (time / 3 >= 1)
	//	{
	//		time = 0;
	//	}
	//}
}

void GameOverScene::Draw(DirectXCommon* directXInit)
{
	ID3D12GraphicsCommandList* cmdList = directXInit->GetCommandList();

	//‰æ‘œ•`‰æ(”w–Ê)
	Sprite::PreDraw(cmdList);

	//‚±‚ÌŠÔ‚É‰æ‘œ
	GameOverBG->Draw();

	Sprite::PostDraw();
	directXInit->ClearDepthBuffer();
	Sprite::PreDraw(cmdList);

	G->Draw();
	A->Draw();
	M->Draw();
	E->Draw();
	O->Draw();
	V->Draw();
	E2->Draw();
	R->Draw();

	Sprite::PostDraw();
}

void GameOverScene::Delete()
{
}
