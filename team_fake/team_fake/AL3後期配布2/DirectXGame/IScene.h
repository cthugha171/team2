#pragma once
#include "Scene.h"
#include "Direct.h"
#include "Input.h"
#include "MouseInput.h"
#include "Camera.h"
#include "WinApp.h"
#include "DirectXCommon.h"


class IScene
{
public:
	virtual void Initialize(DirectXCommon* directXInit) {}//初期化

	virtual void Update(Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp) {}//更新

	virtual void Draw() {}//描画

	virtual void Delete() {}//色々削除

	//シーン管理
	bool IsEnd() {}//終了チェック
	Scene Next() {}//次のシーン

};

