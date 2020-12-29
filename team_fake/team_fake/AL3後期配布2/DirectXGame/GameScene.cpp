#include "GameScene.h"
#include "SceneManager.h"

void GameScene::Initialize(DirectXCommon* directXInit)
{
	this->directXinit = directXInit;
	epos = XMFLOAT3(0, 0, 50);

	deltaTime = new DeltaTime();

	objground = Object3d::Create();
	ground = Model::CreateFromOBJ("ground");
	objground->SetModel(ground);

	objback = Object3d::Create();
	back = Model::CreateFromOBJ("skydome");
	objback->SetModel(back);
	backside = new MoveBack(objback);

	//audio = new Audio();
	//audio->initialize();

	pObj = Object3d::Create();
	pModel = Model::CreateFromOBJ("player");
	pObj->SetModel(pModel);
	player = new Player(100, {0,0},pObj,directXInit->GetDevice());
	player->Initialize();

	eObj = Object3d::Create();
	eModel = Model::CreateFromOBJ("enemy");
	eObj->SetModel(eModel);

	pbModel = Model::CreateFromOBJ("bullet");

	ui = new UI();
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

	objback->Update(matView,matPro);

	backside->Move(input,camera);

	time += deltaTime->deltaTime();
	time2 += deltaTime->deltaTime();
	player->Update(camera, input);


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

	eneSpawn.Update(camera, player);

	playerShot.Update(player, mouse, camera, winApp);

	ui->HpGauge(player->GetHp());

	objground->Update(camera->GetmatView(),camera->GetmatProjection());

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
	//コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = directXinit->GetCommandList();

	//3Dオブジェクト
	Object3d::PreDraw(cmdList);

	//3Dオブジェクトの描画
	//backside->Draw();

	objback->Draw();

	objground->Draw();

	player->Draw();
	
	eneSpawn.Draw();

	playerShot.Draw();


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
