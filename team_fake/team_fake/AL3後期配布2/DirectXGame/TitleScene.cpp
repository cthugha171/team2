#include "TitleScene.h"
#include "SceneManager.h"
#include "SafeDelete.h"
#include "Vector2.h"

void TitleScene::Initialize(DirectXCommon* directXInit)
{
	//デルタタイム
	deltaTime = new DeltaTime();
	//スプライト関係
	Sprite::LoadTexture(0, L"Resources/TitileBG.png");
	Sprite::LoadTexture(1, L"Resources/TitileName.png");
	Sprite::LoadTexture(2, L"Resources/TitilePushKey.png");
	TitleBG = Sprite::Create(0, { 0,0 });
	TitleName = Sprite::Create(1, { 50,-70 });
	TitlePushKey = Sprite::Create(2, { 0,0 });
	//オブジェクト関係
	player = Object3d::Create();
	pModel = Model::CreateFromOBJ("player");
	player->SetModel(pModel);
	XMFLOAT3 rot = player->GetRotation();
	rot.z -= 10;
	player->SetRotation(rot);
	player->SetScale({ 7,7,7 });
	player->SetPosition({ -5,-5,3 });
	se = new Audio();
	se->initialize();
	se->LoadWave(L"Resources/kettei-02.wav");
 	bgm = new Audio();
	bgm->initialize();
	bgm->LoadWave(L"Resources/Cubes.wav");
	dTime = 0;
	time = 0;
	time2 = 0;
	sceneChange = false;
	Cbgm = true;
}

void TitleScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	
	dTime= deltaTime->deltaTime();
	if (bgm->endAudioCheck()|| Cbgm)
	{
		bgm->PlayWave(0.5f);
		Cbgm = false;
	}
	
	if (input->isKeyDown(DIK_SPACE))
	{
		se->PlayWave(0.5f);
		sceneChange = true;
	}

	if (sceneChange)
	{
		time2 += dTime;
		bgm->UpdateFade(0, 0.5, time2);

		if (se->endAudioCheck())
		{
			bgm->Discard();
			SceneManager::instance().ChangeScene("Game");
		}
		
	}
	//PushKeyの色変更
	{
		if (colorChange)
		{
			time += dTime;
			colorGB = Vector2::lerp(1, 0, time / 3);
			TitlePushKey->SetColor({ 1,colorGB,colorGB ,1 });
			if (colorGB<0)
			{
				colorChange = false;
			}
		}

		else if (colorChange==false)
		{
			time += dTime;
			colorGB = Vector2::lerp(0, 1, time / 3);
			TitlePushKey->SetColor({ 1,colorGB,colorGB ,1 });
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

	//Player
	{
		player->Update(camera->GetmatView(), camera->GetmatProjection());
		camera->setEyePos({ 0,10,-100 });
		camera->setTargetPos({ 0,0,0 });
		XMFLOAT3 rot = player->GetRotation();
		rot.y += 1;
		player->SetRotation(rot);
	}
}

void TitleScene::Draw(DirectXCommon* directXInit)
{
	ID3D12GraphicsCommandList* cmdList = directXInit->GetCommandList();

	//画像描画(背面)
	Sprite::PreDraw(cmdList);

	//この間に画像
	TitleBG->Draw();

	Sprite::PostDraw();
	directXInit->ClearDepthBuffer();

	//3Dオブジェクト
	Object3d::PreDraw(cmdList);

	player->Draw();

	Object3d::PostDraw();

	//画像描画(前面)
	Sprite::PreDraw(cmdList);

	//この間に画像
	TitleName->Draw();
	TitlePushKey->Draw();

	Sprite::PostDraw();
}

void TitleScene::Delete()
{
	safe_delete(TitleBG);
	safe_delete(TitleName);
	safe_delete(TitlePushKey);
	safe_delete(player);
	safe_delete(pModel);
	//bgm->Discard();
	//safe_delete(bgm);
}
