#pragma once
#include <dinput.h>
#include <DirectXMath.h>
#include <WinUser.h>
#include "Camera.h"
#include "WinApp.h"
#define DIRECTINPUT_VERSION 0x0800 // DirectInput �̃o�[�W�����w��

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;
class MouseInput
{
public:
	//������
	void initialize(WinApp* winapp);
	//�X�V
	void update();

	XMFLOAT3 GetMousePos(Camera camera, WinApp* winapp);

	//���N���b�N�������ꂽ�u��
	bool isLeftDown();
	//���N���b�N��������Ă����
	bool isLeftState();

	//�E�N���b�N��������ďu��
	bool isRightDown();
	//�E�N���b�N��������Ă��
	bool isRightState();
private:
	IDirectInput8* m_pDinput;
	IDirectInputDevice8* m_pDMouse;//�}�E�X�f�o�C�X
	DIMOUSESTATE MouseState;//�}�E�X���
	DIMOUSESTATE OldMouseState;
	const int mInputNum = 0x80;
	POINT mousepos;
};

