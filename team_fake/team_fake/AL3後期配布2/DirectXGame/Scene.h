#pragma once
#include <d3dx12.h>
#include"Input.h"

class Scene
{
public:
	//������
	virtual void Initialize(ID3D12Device* dev, HWND hwnd, HINSTANCE hinstance) {}
	//�X�V
	virtual void Update() {}
	//���
	virtual void Release() {}
};