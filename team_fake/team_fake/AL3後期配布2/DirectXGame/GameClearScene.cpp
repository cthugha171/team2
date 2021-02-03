#include "GameClearScene.h"
#include "SceneManager.h"
#include "SafeDelete.h"
#include "Vector2.h"

void GameClearScene::Initialize(DirectXCommon* directXInit)
{
	//デルタタイム
	deltaTime = new DeltaTime();
	//スプライト関係
	Sprite::LoadTexture(0, L"Resources/G.png");
	Sprite::LoadTexture(1, L"Resources/A.png");
	Sprite::LoadTexture(2, L"Resources/M.png");
	Sprite::LoadTexture(3, L"Resources/E.png");
	Sprite::LoadTexture(4, L"Resources/C.png");
	Sprite::LoadTexture(5, L"Resources/L.png");
	//Sprite::LoadTexture(6, L"Resources/E2.png");
	Sprite::LoadTexture(6, L"Resources/R.png");
	Sprite::LoadTexture(7, L"Resources/GameOverBG.png");
	Sprite::LoadTexture(8, L"Resources/TitilePushKey.png");
	clearBG = Sprite::Create(8, { 0,0 });
	clearPushKey = Sprite::Create(9, { 0,0 });
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
	C = Sprite::Create(4, { 450,550 });
	cx = 0;
	cy = 0;
	XMFLOAT2 o = XMFLOAT2(cx, cy);
	C->SetSize(o);
	L = Sprite::Create(5, { 700,550 });
	lx = 0;
	ly = 0;
	XMFLOAT2 v = XMFLOAT2(lx, ly);
	L->SetSize(v);
	E2 = Sprite::Create(3, { 950,550 });
	e2x = 0;
	e2y = 0;
	XMFLOAT2 e2 = XMFLOAT2(e2x, e2y);
	E2->SetSize(e2);
	A2 = Sprite::Create(1, { 1200,550 });
	a2x = 0;
	a2y = 0;
	XMFLOAT2 a2 = XMFLOAT2(a2x, a2y);
	A2->SetSize(a2);
	R = Sprite::Create(6, { 1450,550 });
	rx = 0;
	ry = 0;
	XMFLOAT2 r = XMFLOAT2(rx, ry);
	R->SetSize(r);
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

void GameClearScene::Update(Input* input, MouseInput* mouse, Camera* camera, WinApp* winApp)
{
	dTime = deltaTime->deltaTime();
	if (bgm->endAudioCheck() || Cbgm)
	{
		bgm->PlayWave(0.5f);
		Cbgm = false;
	}

	if (input->isKeyDown(DIK_SPACE))
	{
		se->PlayWave(1);
		sceneChange = true;
	}

	if (sceneChange)
	{
		time2 += dTime;
		bgm->UpdateFade(0, 0.5, time2);

		if (se->endAudioCheck())
		{
			bgm->Discard();
			SceneManager::instance().ChangeScene("Title");
		}

	}
	//gameclear
	{
		time += dTime;

		if (gx <= 184)
		{
			gx += 2;
			gy += 2;
			XMFLOAT2 g = XMFLOAT2(gx, gy);
			G->SetSize(g);
		}
		if (ax <= 184 && time >= 0.3)
		{
			ax += 2;
			ay += 2;
			XMFLOAT2 a = XMFLOAT2(ax, ay);
			A->SetSize(a);
		}
		if (mx <= 184 && time >= 0.6)
		{
			mx += 2;
			my += 2;
			XMFLOAT2 m = XMFLOAT2(mx, my);
			M->SetSize(m);
		}
		if (ex <= 184 && time >= 0.9)
		{
			ex += 2;
			ey += 2;
			XMFLOAT2 e = XMFLOAT2(ex, ey);
			E->SetSize(e);
		}
		if (cx <= 184 && time >= 1.2)
		{
			cx += 2;
			cy += 2;
			XMFLOAT2 o = XMFLOAT2(cx, cy);
			C->SetSize(o);
		}
		if (lx <= 184 && time >= 1.5)
		{
			lx += 2;
			ly += 2;
			XMFLOAT2 v = XMFLOAT2(lx, ly);
			L->SetSize(v);
		}
		if (e2x <= 184 && time >= 1.8)
		{
			e2x += 2;
			e2y += 2;
			XMFLOAT2 e2 = XMFLOAT2(e2x, e2y);
			E2->SetSize(e2);
		}
		if (a2x <= 184 && time >= 2.1)
		{
			a2x += 2;
			a2y += 2;
			XMFLOAT2 e2 = XMFLOAT2(a2x, a2y);
			A2->SetSize(e2);
		}
		if (rx <= 184 && time >= 2.4)
		{
			rx += 2;
			ry += 2;
			XMFLOAT2 r = XMFLOAT2(rx, ry);
			R->SetSize(r);
		}
	}
	//PushKeyの色変更
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

	//画像描画(背面)
	Sprite::PreDraw(cmdList);

	//この間に画像
	clearBG->Draw();

	Sprite::PostDraw();
	directXInit->ClearDepthBuffer();

	// 画像描画(前面)
		Sprite::PreDraw(cmdList);

	//この間に画像
		G->Draw();
		A->Draw();
		M->Draw();
		E->Draw();
		C->Draw();
		L->Draw();
		E2->Draw();
		A2->Draw();
		R->Draw();
	clearPushKey->Draw();

	Sprite::PostDraw();
}

void GameClearScene::Delete()
{

	safe_delete(clearBG);
	safe_delete(G);
	safe_delete(A);
	safe_delete(M);
	safe_delete(E);
	safe_delete(C);
	safe_delete(L);
	safe_delete(E2);
	safe_delete(A2);
	safe_delete(R);
	safe_delete(clearPushKey);
}
