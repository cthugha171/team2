#pragma once
#include <dinput.h>
#include <DirectXMath.h>
#include <WinUser.h>
#include "Camera.h"
#include "WinApp.h"
#define DIRECTINPUT_VERSION 0x0800 // DirectInput のバージョン指定

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;
class MouseInput
{
public:
	//初期化
	void initialize(WinApp* winapp);
	//更新
	void update();

	XMFLOAT3 GetMousePos(Camera camera, WinApp* winapp);

	bool Leftclick();
	bool Rightclick();
private:
	IDirectInput8* m_pDinput;
	IDirectInputDevice8* m_pDMouse;//マウスデバイス
	DIMOUSESTATE MouseState;//マウス状態
	POINT mousepos;
};

