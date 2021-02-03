#include "GameOverScene.h"
#include "SceneManager.h"
#include "SafeDelete.h"
#include "Vector2.h"

XMFLOAT2 a;
void GameOverScene::Initialize(DirectXCommon* directXInit)
{
	deltaTime = new DeltaTime();
	time = 0;
	time2 = 0;
	time3 = 0;
	Sprite::LoadTexture(0, L"Resources/G.png");
	Sprite::LoadTexture(1, L"Resources/A.png");
	Sprite::LoadTexture(2, L"Resources/M.png");
	Sprite::LoadTexture(3, L"Resources/E.png");
	Sprite::LoadTexture(4, L"Resources/O.png");
	Sprite::LoadTexture(5, L"Resources/V.png");
	Sprite::LoadTexture(6, L"Resources/E2.png");
	Sprite::LoadTexture(7, L"Resources/R.png");
	Sprite::LoadTexture(8, L"Resources/GameOverBG.png");
	Sprite::LoadTexture(9, L"Resources/TitilePushKey.png");
	GameOverBG = Sprite::Create(8, { 0,0 });
	overPushKey = Sprite::Create(9, { 0,0 });
	G = Sprite::Create(0, { 500,250 });
	gx = 0;
	gy = 0;
	XMFLOAT2 g = XMFLOAT2(gx, gy);
	G->SetSize(g);
	A = Sprite::Create(1, { 750,250 });
	ax = 0;
	ay = 0;
	XMFLOAT2 a = XMFLOAT2(ax, ay);
	A->SetSize(a);
	M = Sprite::Create(2, { 1000,250 });
	mx = 0;
	my = 0;
	XMFLOAT2 m = XMFLOAT2(mx, my);
	M->SetSize(m);
	E = Sprite::Create(3, { 1270,250 });
	ex = 0;
	ey = 0;
	XMFLOAT2 e = XMFLOAT2(ex, ey);
	E->SetSize(e);
	O = Sprite::Create(4, { 500,550 });
	ox = 0;
	oy = 0;
	XMFLOAT2 o = XMFLOAT2(ox, oy);
	O->SetSize(o);
	V = Sprite::Create(5, { 750,550 });
	vx = 0;
	vy = 0;
	XMFLOAT2 v = XMFLOAT2(vx, vy);
	V->SetSize(v);
	E2 = Sprite::Create(6, { 1000,550 });
	e2x = 0;
	e2y = 0;
	XMFLOAT2 e2 = XMFLOAT2(e2x, e2y);
	E2->SetSize(e2);
	R = Sprite::Create(7, { 1250,550 });
	rx = 0;
	ry = 0;
	XMFLOAT2 r = XMFLOAT2(rx, ry);
	R->SetSize(r);
	se = new Audio();
	se->initialize();
	se->LoadWave(L"Resources/kettei-02.wav");
	bgm = new Audio();
	bgm->initialize();
	bgm->LoadWave(L"Resources/gameover3.wav");
	Cbgm = true;
}

void GameOverScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	if (Cbgm)
	{
		bgm->PlayWave(0.5f);
		Cbgm = false;
	}
	
	if (input->isKeyDown(DIK_SPACE))
	{
		se->PlayWave();
		sceneChange = true;
	}

	if (sceneChange)
	{
		time3 += dTime;
		bgm->UpdateFade(0, 0.5, time3);
		if (se->endAudioCheck())
		{
			bgm->Discard();
			SceneManager::instance().ChangeScene("Title");
		}
	}

	dTime= deltaTime->deltaTime();
	//gameover
	{
		time += dTime;

		if (gx <= 184)
		{
			gx += 2;
			gy += 2;
			XMFLOAT2 g = XMFLOAT2(gx, gy);
			G->SetSize(g);
		}
		if (ax <= 184&& time>=0.6)
		{
			ax += 2;
			ay += 2;
			XMFLOAT2 a = XMFLOAT2(ax, ay);
			A->SetSize(a);
		}
		if (mx <= 184 && time >= 1.2)
		{
			mx += 2;
			my += 2;
			XMFLOAT2 m = XMFLOAT2(mx, my);
			M->SetSize(m);
		}
		if (ex <= 184 && time >= 1.8)
		{
			ex += 2;
			ey += 2;
			XMFLOAT2 e = XMFLOAT2(ex, ey);
			E->SetSize(e);
		}
		if (ox <= 184 && time >= 2.4)
		{
			ox += 2;
			oy += 2;
			XMFLOAT2 o = XMFLOAT2(ox, oy);
			O->SetSize(o);
		}
		if (vx <= 184 && time >= 3.0)
		{
			vx += 2;
			vy += 2;
			XMFLOAT2 v = XMFLOAT2(vx, vy);
			V->SetSize(v);
		}
		if (e2x <= 184 && time >= 3.6)
		{
			e2x += 2;
			e2y += 2;
			XMFLOAT2 e2 = XMFLOAT2(e2x, e2y);
			E2->SetSize(e2);
		}
		if (rx <= 184 && time >= 4.2)
		{
			rx += 2;
			ry += 2;
			XMFLOAT2 r = XMFLOAT2(rx, ry);
			R->SetSize(r);
		}
	}

	//“_–Å—p
	if(time>0)
	{
		if (colorChange)
		{
			time2 += dTime;
			colorGB = Vector2::lerp(1, 0, time2 / 3);
			overPushKey->SetColor({ 1,colorGB,colorGB ,1 });
			if (colorGB < 0)
			{
				colorChange = false;
			}
		}

		else if (colorChange == false)
		{
			time2 += dTime;
			colorGB = Vector2::lerp(0, 1, time2 / 3);
			overPushKey->SetColor({ 1,colorGB,colorGB ,1 });
			if (colorGB >= 1)
			{
				colorChange = true;
			}
		}

		if (time2 / 3 >= 1)
		{
			time2 = 0;
		}
	}
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
	overPushKey->Draw();

	Sprite::PostDraw();
}

void GameOverScene::Delete()
{
}
