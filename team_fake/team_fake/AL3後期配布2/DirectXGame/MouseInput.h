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

	//左クリックが押された瞬間
	bool isLeftDown();
	//左クリックが押されている間
	bool isLeftState();

	//右クリックが押されて瞬間
	bool isRightDown();
	//右クリックが押されてる間
	bool isRightState();
private:
	IDirectInput8* m_pDinput;
	IDirectInputDevice8* m_pDMouse;//マウスデバイス
	DIMOUSESTATE MouseState;//マウス状態
	DIMOUSESTATE OldMouseState;
	const int mInputNum = 0x80;
	POINT mousepos;
};

