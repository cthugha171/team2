#include "TitleScene.h"
#include "SceneManager.h"
#include "SafeDelete.h"
#include "Vector2.h"

void TitleScene::Initialize(DirectXCommon* directXInit)
{
	//�f���^�^�C��
	deltaTime = new DeltaTime();
	//�X�v���C�g�֌W
	Sprite::LoadTexture(0, L"Resources/TitileBG.png");
	Sprite::LoadTexture(1, L"Resources/TitileName.png");
	Sprite::LoadTexture(2, L"Resources/TitilePushKey.png");
	TitleBG = Sprite::Create(0, { 0,0 });
	TitleName = Sprite::Create(1, { 50,-70 });
	TitlePushKey = Sprite::Create(2, { 0,0 });
	//�I�u�W�F�N�g�֌W
	player = Object3d::Create();
	pModel = Model::CreateFromOBJ("player");
	player->SetModel(pModel);
	XMFLOAT3 rot = player->GetRotation();
	rot.z -= 10;
	player->SetRotation(rot);
	player->SetScale({ 5,5,5 });
	player->SetPosition({ -5,-5,0 });
}

void TitleScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	if (input->isKeyDown(DIK_SPACE))
	{
		SceneManager::instance().ChangeScene("Game");
	}

	//PushKey�̐F�ύX
	{
		if (colorGB > 0)
		{
			time += deltaTime->deltaTime();
			colorGB = Vector2::lerp(1, 0, time / 3);
			TitlePushKey->SetColor({ 1,colorGB,colorGB ,1 });
		}
		else if (colorGB <= 1)
		{
			time += deltaTime->deltaTime();
			colorGB = Vector2::lerp(0, 1, time / 3);
			TitlePushKey->SetColor({ 1,colorGB,colorGB ,1 });
		}

		if (time / 3 >= 1)
		{
			time = 0;
		}
	}

	//Player
	{
		player->Update(camera->GetmatView(), camera->GetmatProjection());
		XMFLOAT3 rot = player->GetRotation();
		rot.y += 1;
		player->SetRotation(rot);
	}
}

void TitleScene::Draw(DirectXCommon* directXInit)
{
	ID3D12GraphicsCommandList* cmdList = directXInit->GetCommandList();

	//�摜�`��(�w��)
	Sprite::PreDraw(cmdList);

	//���̊Ԃɉ摜
	TitleBG->Draw();

	Sprite::PostDraw();
	directXInit->ClearDepthBuffer();

	//3D�I�u�W�F�N�g
	Object3d::PreDraw(cmdList);

	player->Draw();

	Object3d::PostDraw();

	//�摜�`��(�O��)
	Sprite::PreDraw(cmdList);

	//���̊Ԃɉ摜
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
}
