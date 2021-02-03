#include "GameScene.h"
#include "SceneManager.h"

void GameScene::Initialize(DirectXCommon* directXInit)
{
	this->directXinit = directXInit;
	epos = XMFLOAT3(0, 0, 100);

	deltaTime = new DeltaTime();

	objground = Object3d::Create();
	objground2 = Object3d::Create();
	objback = Object3d::Create();
	pObj = Object3d::Create();
	eObj = Object3d::Create();

	ground = Model::CreateFromOBJ("ground");
	back = Model::CreateFromOBJ("skydome");
	pModel = Model::CreateFromOBJ("player");
	eModel = Model::CreateFromOBJ("enemy");
	pbModel = Model::CreateFromOBJ("bullet");
	building = Model::CreateFromOBJ("building");

	//audio = new Audio();
	//audio->initialize();

	se = new Audio();
	se->initialize();
	se->LoadWave(1, L"Resources/shot.wav");
	se->LoadWave(2, L"Resources/se_dead.wav");
	bgm = new Audio();
	bgm->initialize();
	bgm->LoadWave(1, L"Resources/bgm_game.wav");

	objground->SetModel(ground);
	objground2->SetModel(ground);
	objback->SetModel(back);
	pObj->SetModel(pModel);
	eObj->SetModel(eModel);

	backside = new MoveBack(objback);
	player = new Player(100, {0,10},pObj,directXInit->GetDevice());
	moveGround = new MoveGround();
	ui = new UI();
	eneSpawn = new EnemySpawner();
	playerShot = new PlayerShot();
	others = new CreateObject();
	bSpawn = new BuildingSpawner();

	player->Initialize();
	moveGround->Initialize(objground, objground2, 5);
	ui->Initialize();
	ui->InitHP(player->GetHp());

	dTime = 0;
	time2 = 0;
	sceneChange = false;
	Cbgm = true;
}

void GameScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	dTime = deltaTime->deltaTime();
	if (bgm->endAudioCheck() || Cbgm)
	{
		bgm->PlayWave(1, 0.3f);
		Cbgm = false;
	}

	if(player->IsDead())
	{
		time2 += dTime;
		bgm->UpdateFade(0, 0.5, time2);

			bgm->Discard();
			SceneManager::instance().ChangeScene("Clear");
		
	}
	if (eneSpawn->GetEndFlag() >= 100)
	{
		time2 += dTime;
		bgm->UpdateFade(0, 0.5, time2);

			bgm->Discard();
			SceneManager::instance().ChangeScene("Over");
		
	}
	XMMATRIX matView = camera->GetmatView();
	XMMATRIX matPro = camera->GetmatProjection();


	backside->Move(input,camera);
	
	time += dTime;

	epos = XMFLOAT3(epos.x, player->GetPosition().y, epos.z);


	if (player->Shot(mouse))
	{
		se->PlayWave(1);
		playerShot->Shot(player->GetPosition(), others->create(pbModel));
	}


	if (time / 2>=1)
	{
		eneSpawn->spawn(epos,others->create(eModel),directXinit->GetDevice());
		bSpawn->Spawn({ player->GetPosition().x,epos.y }, {100,0,0}, others->create(building), others->create(building));
		time = 0;
	}


	objback->Update(matView,matPro);
	player->Update(camera, input);
	moveGround->Update(camera);
	eneSpawn->Update(camera, player);
	playerShot->Update(player, mouse, camera, winApp);
	bSpawn->Update(camera);
	//objground->Update(camera->GetmatView(),camera->GetmatProjection());

	ui->HpGauge(player->GetHp());


	for (auto it = playerShot->shotList.begin(); it != playerShot->shotList.end();)
	{
		for (auto itr = eneSpawn->enemyList.begin(); itr != eneSpawn->enemyList.end();)
		{
			if ((*it)->Collisions(*itr))
			{
				(*itr)->Damage(10);
			}
			if ((*itr)->IsDead())
			{
				se->PlayWave(2);
			}
			
			itr++;
		}
		it++;
	}

	for (auto itr = eneSpawn->enemyList.begin(); itr != eneSpawn->enemyList.end();)
	{
		if ((*itr)->Collisions(player))
		{
			player->Damage(20);
			(*itr)->Damage(10);
		}
		itr++;
	}

	for (auto itre = bSpawn->BuildingList.begin(); itre != bSpawn->BuildingList.end();)
	{
		if ((*itre)->Collitions(player, building))
		{
			player->Damage(1);
		}
		itre++;
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

	//objground->Draw();

	moveGround->Draw();

	player->Draw();
	
	eneSpawn->Draw();

	bSpawn->Draw();

	playerShot->Draw();


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
	safe_delete(others);
	safe_delete(pObj);
	safe_delete(eObj);
	safe_delete(objground);
	safe_delete(objground2);
	safe_delete(objback);
	safe_delete(deltaTime);
	safe_delete(pbModel);
	safe_delete(pModel);
	safe_delete(eModel);
	safe_delete(back);
	safe_delete(ground);
	safe_delete(building);
	safe_delete(player);
	safe_delete(backside);
	safe_delete(ui);
	safe_delete(eneSpawn);
	safe_delete(playerShot);
	safe_delete(bSpawn);
}
