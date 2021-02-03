#include "GameClearScene.h"
#include "SceneManager.h"
#include "SafeDelete.h"
#include "Vector2.h"

void GameClearScene::Initialize(DirectXCommon* directXInit)
{
	//�f���^�^�C��
	deltaTime = new DeltaTime();
	//�X�v���C�g�֌W
	Sprite::LoadTexture(0, L"Resources/TitileBG.png");
	Sprite::LoadTexture(1, L"Resources/TitileName.png");
	Sprite::LoadTexture(2, L"Resources/TitilePushKey.png");
	clearBG = Sprite::Create(0, { 0,0 });
	clearName = Sprite::Create(1, { 50,-70 });
	clearPushKey = Sprite::Create(2, { 0,0 });
	se = new Audio();
	se->initialize();
	bgm = new Audio();
	bgm->initialize();
	dTime = 0;
	time = 0;
	time2 = 0;
	sceneChange = false;
	Cbgm = true;
}

void GameClearScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	dTime = deltaTime->deltaTime();
	if (bgm->endAudioCheck() || Cbgm)
	{
		bgm->PlayWave("Resources/Cubes.wav", 0.5f);
		Cbgm = false;
	}

	if (input->isKeyDown(DIK_SPACE))
	{
		se->PlayWave("Resources/kettei-02.wav");
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
	//PushKey�̐F�ύX
	{
		if (colorChange)
		{
			time += dTime;
			colorGB = Vector2::lerp(1, 0, time / 3);
			clearPushKey->SetColor({ 1,colorGB,colorGB ,1 });
			if (colorGB < 0)
			{
				colorChange = false;
			}
		}

		else if (colorChange == false)
		{
			time += dTime;
			colorGB = Vector2::lerp(0, 1, time / 3);
			clearPushKey->SetColor({ 1,colorGB,colorGB ,1 });
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

void GameClearScene::Draw(DirectXCommon* directXInit)
{
	ID3D12GraphicsCommandList* cmdList = directXInit->GetCommandList();

	//�摜�`��(�w��)
	Sprite::PreDraw(cmdList);

	//���̊Ԃɉ摜
	clearBG->Draw();

	Sprite::PostDraw();
	directXInit->ClearDepthBuffer();

	// �摜�`��(�O��)
		Sprite::PreDraw(cmdList);

	//���̊Ԃɉ摜
	clearName->Draw();
	clearPushKey->Draw();

	Sprite::PostDraw();
}

void GameClearScene::Delete()
{

	safe_delete(clearBG);
	safe_delete(clearName);
	safe_delete(clearPushKey);
}
