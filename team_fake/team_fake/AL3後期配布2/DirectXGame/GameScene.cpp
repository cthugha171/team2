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
	se->LoadWave(L"Resources/shot.wav");
	se2 = new Audio();
	se2->initialize();
	se2->LoadWave(L"Resources/se_dead.wav");
	bgm = new Audio();
	bgm->initialize();
	bgm->LoadWave(L"Resources/bgm_game.wav");

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
	time = 0;
	time2 = 0;
	time3 = 0;
	sceneChange = false;
	Cbgm = true;
}

void GameScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	dTime = deltaTime->deltaTime();
	if (bgm->endAudioCheck() || Cbgm)
	{
		bgm->PlayWave(0.3f);
		Cbgm = false;
	}

	if(player->IsDead()&&time<60)
	{
		time2 += dTime;
		bgm->UpdateFade(0, 0.5, time2);

			bgm->Discard();
			SceneManager::instance().ChangeScene("Over");
		
	}
	if (time>=30)
	{
		time2 += dTime;
		bgm->UpdateFade(0, 0.5, time2);

			bgm->Discard();
			SceneManager::instance().ChangeScene("Clear");
		
	}
	XMMATRIX matView = camera->GetmatView();
	XMMATRIX matPro = camera->GetmatProjection();


	backside->Move(input,camera);
	
	time += dTime;
	time3 += dTime;

	epos = XMFLOAT3(epos.x, player->GetPosition().y, epos.z);


	if (player->Shot(mouse))
	{
		se->PlayWave();
		playerShot->Shot(player->GetPosition(), others->create(pbModel));
	}


	if (time3 / 2>=1)
	{
		eneSpawn->spawn(epos,others->create(eModel),directXinit->GetDevice());
		bSpawn->Spawn({ player->GetPosition().x,epos.y }, {100,0,0}, others->create(building), others->create(building));
		time3 = 0;
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
				se2->PlayWave();
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
	//コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = directXinit->GetCommandList();

	//3Dオブジェクト
	Object3d::PreDraw(cmdList);

	//3Dオブジェクトの描画
	//backside->Draw();

	objback->Draw();

	//objground->Draw();

	moveGround->Draw();

	player->Draw();
	
	eneSpawn->Draw();

	bSpawn->Draw();

	playerShot->Draw();


	//3Dオブジェクト描画後取得
	Object3d::PostDraw();

	//スプライトの描画開始
	Sprite::PreDraw(cmdList);

	ui->HpDraw();

	//スプライトの描画終了
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
