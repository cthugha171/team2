#include "WinApp.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "Camera.h"
#include "MouseInput.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	// 汎用機能
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Camera* camera = nullptr;
	Input* input = nullptr;	
	MouseInput* mouse = nullptr;
	GameScene* gameScene = nullptr;

	// ゲームウィンドウの作成
	win = new WinApp();
	win->CreateGameWindow();
		
	//DirectX初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// 入力の初期化
	input = new Input();
	input->initialize(win);

	mouse = new MouseInput();
	mouse->initialize(win);

	//カメラの初期化
	camera = new Camera();
	camera->Initialize(win);

	// スプライト静的初期化
	if (!Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	
	// 3Dオブジェクト静的初期化
	if (!Object3d::StaticInitialize(dxCommon->GetDevice())) {
		assert(0);
		return 1;
	}
#pragma endregion

	//シーン管理
	SceneManager::instance().Add("Title", new TitleScene);
	SceneManager::instance().Add("Game", new GameScene);
	SceneManager::instance().Add("Over", new GameOverScene);
	SceneManager::instance().StartScene("Title");

	
	// メインループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage()) {break; }
		// 描画開始
		dxCommon->PreDraw();

		// 入力関連の毎フレーム処理
		input->update();
		mouse->update();
		camera->update();
		// ゲームシーンの毎フレーム処理

		//シーンの更新
		SceneManager::instance().update(dxCommon, input, mouse, camera, win);

		// 描画終了
		dxCommon->PostDraw();
	}
	// 各種解放
	safe_delete(input);
	safe_delete(dxCommon);

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	safe_delete(win);

	return 0;
}