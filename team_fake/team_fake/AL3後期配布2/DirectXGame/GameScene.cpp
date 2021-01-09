#include "GameScene.h"
#include "SceneManager.h"

void GameScene::Initialize(DirectXCommon* directXInit)
{
	this->directXinit = directXInit;
	epos = XMFLOAT3(0, 0, 50);

	deltaTime = new DeltaTime();

	objground = Object3d::Create();
	objback = Object3d::Create();
	pObj = Object3d::Create();
	eObj = Object3d::Create();

	ground = Model::CreateFromOBJ("ground");
	back = Model::CreateFromOBJ("skydome");
	pModel = Model::CreateFromOBJ("player");
	eModel = Model::CreateFromOBJ("enemy");
	pbModel = Model::CreateFromOBJ("bullet");

	//audio = new Audio();
	//audio->initialize();


	objground->SetModel(ground);
	objback->SetModel(back);
	pObj->SetModel(pModel);
	eObj->SetModel(eModel);

	backside = new MoveBack(objback);
	player = new Player(100, {0,0},pObj,directXInit->GetDevice());
	ui = new UI();

	player->Initialize();
	ui->Initialize();
	ui->InitHP(player->GetHp());
}

void GameScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	if(player->IsDead())
	{
		SceneManager::instance().ChangeScene("Over");
	}
	if (eneSpawn.GetEndFlag() >= 100)
	{
		SceneManager::instance().ChangeScene("Over");
	}
	XMMATRIX matView = camera->GetmatView();
	XMMATRIX matPro = camera->GetmatProjection();


	backside->Move(input,camera);

	time += deltaTime->deltaTime();
	time2 += deltaTime->deltaTime();


	if (player->Shot(mouse))
	{
		playerShot.Shot(player->GetPosition(), others.create(pbModel));
		time2 = 0;
	}


	if (time / 2>=1)
	{
		eneSpawn.spawn(epos,others.create(eModel),directXinit->GetDevice());
		time = 0;
	}


	objback->Update(matView,matPro);
	player->Update(camera, input);
	eneSpawn.Update(camera, player);
	playerShot.Update(player, mouse, camera, winApp);
	objground->Update(camera->GetmatView(),camera->GetmatProjection());

	ui->HpGauge(player->GetHp());


	for (auto it = playerShot.shotList.begin(); it != playerShot.shotList.end();)
	{
		for (auto itr = eneSpawn.enemyList.begin(); itr != eneSpawn.enemyList.end();)
		{
			if ((*it)->Collisions(*itr))
			{
				(*itr)->Damage(10);
			}
			
			itr++;
		}
		it++;
	}

	for (auto itr = eneSpawn.enemyList.begin(); itr != eneSpawn.enemyList.end();)
	{
		if ((*itr)->Collisions(player))
		{
			player->Damage(20);
			(*itr)->Damage(10);
		}
		itr++;
	}
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

void GameScene::Draw(DirectXCommon* directXinit)
{
	//�R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = directXinit->GetCommandList();

	//3D�I�u�W�F�N�g
	Object3d::PreDraw(cmdList);

	//3D�I�u�W�F�N�g�̕`��
	//backside->Draw();

	objback->Draw();

	objground->Draw();

	player->Draw();
	
	eneSpawn.Draw();

	playerShot.Draw();


	//3D�I�u�W�F�N�g�`���擾
	Object3d::PostDraw();

	//�X�v���C�g�̕`��J�n
	Sprite::PreDraw(cmdList);

	ui->HpDraw();

	//�X�v���C�g�̕`��I��
	Sprite::PostDraw();
}

void GameScene::Delete()
{
	/*audio->Discard();
	safe_dalete(audio);*/
	safe_delete(pObj);
	safe_delete(eObj);
	safe_delete(objground);
	safe_delete(objback);
	safe_delete(deltaTime);
	safe_delete(pbModel);
	safe_delete(pModel);
	safe_delete(eModel);
	safe_delete(back);
	safe_delete(ground);
	safe_delete(player);
	safe_delete(backside);
	safe_delete(ui);
	eneSpawn.~EnemySpawner();
	playerShot.~PlayerShot();
	others.~CreateObject();
}
