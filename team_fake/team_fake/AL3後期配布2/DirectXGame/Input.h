#pragma once

#include "WinApp.h"

#include<dinput.h>

#define DIRECTINPUT_VERSION 0x0800 // DirectInput のバージョン指定

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class Input
{
public:
	//コンストラクタ
	Input();
	//デスストラクタ
	~Input();

	//初期化
	void initialize(WinApp* winapp);
	//更新
	void update();

	//キーが押された瞬間
	bool isKeyDown(int key);
	//キーが押されている間
	bool isKeyState(int key);
	//キーが離された瞬間
	bool isKeyUp(int key);

private:
	IDirectInput8* m_pDinput;
	IDirectInputDevice8* m_pDevkeyborad;

	HRESULT mResult;
	//この値との論理積で入力を取る
	const int mInputNum = 0x80;

	//キー入力
	BYTE mCurKey[256];
	BYTE mPreKey[256];
};

