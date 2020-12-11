#pragma once
#include <d3dx12.h>
#include"Input.h"

class Scene
{
public:
	//初期化
	virtual void Initialize(ID3D12Device* dev, HWND hwnd, HINSTANCE hinstance) {}
	//更新
	virtual void Update() {}
	//解放
	virtual void Release() {}
};