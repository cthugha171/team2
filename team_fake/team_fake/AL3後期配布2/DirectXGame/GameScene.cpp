#include "GameScene.h"

void GameScene::Initialize(DirectXCommon* directXInit)
{
	this->directXinit = directXInit;

	objground = Object3d::Create();
	ground = Model::CreateFromOBJ("ground");
	objground->SetModel(ground);

	//audio = new Audio();
	//audio->initialize();

	pObj = Object3d::Create();
	pModel = Model::CreateFromOBJ("player");
	pObj->SetModel(pModel);
	player = new Player(500, {0,0},pObj,directXInit->GetDevice());
	player->Initialize();

	eObj = Object3d::Create();
	eModel = Model::CreateFromOBJ("player");
	eObj->SetModel(eModel);
	enemy = new Enemy();
	enemy->Initialize(escape, { 50,0,50 }, eObj, directXInit->GetDevice());

	pbObj = Object3d::Create();
	pbModel = Model::CreateFromOBJ("player");
	pbObj->SetModel(pbModel);

	//ui = new UI(directXInit->GetDev(), directXInit->GetcmdList());
	//ui->Initialize();
	//ui->InitHP(player->GetHp());
}

void GameScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	player->Update(camera, input);

	//if (player->Shot(mouse))
	//{
	//	playerShot.Shot(player->GetPosition(), pbObj);
	//}

	//ui->HpGauge(player->GetHp(), { 50, 50 });

	objground->Update();

	/*if (input->isKeyDown(DIK_ESCAPE))
	{
		time = 0;
		audio->PlayWave("Resources/Alarm01.wav", 1);
		oto = true;
	}

	if (oto)
	{
		audio->UpdateFade(0, 5, time);
	}*/
}

void GameScene::Draw()
{
	//�R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = directXinit->GetCommandList();

	//3D�I�u�W�F�N�g
	Object3d::PreDraw(cmdList);

	//3D�I�u�W�F�N�g�̕`��
	objground->Draw();

	player->Draw();

	enemy->Draw();

	//3D�I�u�W�F�N�g�`���擾
	Object3d::PostDraw();
}

void GameScene::Delete()
{
	/*audio->Discard();
	safe_dalete(audio);*/
	safe_delete(player);
	safe_delete(enemy);
	//safe_dalete(ui);
}
