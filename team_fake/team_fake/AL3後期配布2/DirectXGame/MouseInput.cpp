#include "MouseInput.h"
#include <stdio.h>
#include <Windows.h>
#include "WinApp.h"
#include "Camera.h"

void MouseInput::initialize(WinApp*winapp)
{
	HRESULT re = S_FALSE;
	//DirectInputの生成
	re=DirectInput8Create(
		winapp->GetInstance(),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_pDinput,nullptr);
	//マウス用デバイスの生成
	re = m_pDinput->CreateDevice(GUID_SysMouse, &m_pDMouse,NULL);
	//データフォーマットを設定
	re = m_pDMouse->SetDataFormat(&c_dfDIMouse);
	//モードを設定
	re = m_pDMouse->SetCooperativeLevel(winapp->GetHwnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	//デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;//相対値モードで設定
	re = m_pDMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
}

void MouseInput::update()
{
	//1フレーム前の
	OldMouseState = MouseState;

	m_pDMouse->Acquire();

	HRESULT hr = m_pDMouse->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState);
	if (hr == DIERR_INPUTLOST)
	{
		m_pDMouse->Acquire();
		hr = m_pDMouse->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState);
	}
}

XMFLOAT3 MouseInput::GetMousePos(Camera camera,WinApp* winapp)
{
	GetCursorPos(&mousepos);
	float x = mousepos.x;//スクリーン座標X
	float y = mousepos.y;//スクリーン座標Y
	int screen_w = winapp->GetWindowWidthSize();//ビューポートWidth
	int screen_h = winapp->GetWindowHeightSize();//ビューポートHeight
	XMMATRIX view = camera.GetinversView();
	XMMATRIX proj = camera.GetinversProjection();
	XMMATRIX VP = XMMatrixIdentity();
	VP = XMMatrixSet
	(
		screen_w / 2, 0, 0, 0,
		0,-screen_h / 2, 0, 0,
		0,0,1,0,
		screen_w/2,screen_h/2,0,1

	);
	XMMATRIX ViewPort = XMMatrixInverse(nullptr,VP);
	XMMATRIX tmp = ViewPort * proj * view;
	XMFLOAT3* screenpos;
	screenpos = &XMFLOAT3(x, y, 1);
	XMVECTOR pout= XMVector3TransformCoord(XMLoadFloat3(screenpos),tmp);
	XMFLOAT3 LastPos;
	XMStoreFloat3(&LastPos, pout);
	return LastPos;
}

bool MouseInput::isLeftDown()
{
	return (MouseState.rgbButtons[0] & mInputNum) && !(OldMouseState.rgbButtons[0] & mInputNum);
}

bool MouseInput::isLeftState()
{
	return (MouseState.rgbButtons[0] & mInputNum) && (OldMouseState.rgbButtons[0] & mInputNum);
}

bool MouseInput::isRightDown()
{
	return (MouseState.rgbButtons[1] & mInputNum) && !(OldMouseState.rgbButtons[1] & mInputNum);
}

bool MouseInput::isRightState()
{
	return (MouseState.rgbButtons[1] & mInputNum) && (OldMouseState.rgbButtons[1] & mInputNum);
}


