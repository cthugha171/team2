#pragma once

#include "WinApp.h"

#include<dinput.h>

#define DIRECTINPUT_VERSION 0x0800 // DirectInput �̃o�[�W�����w��

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class Input
{
public:
	//�R���X�g���N�^
	Input();
	//�f�X�X�g���N�^
	~Input();

	//������
	void initialize(WinApp* winapp);
	//�X�V
	void update();

	//�L�[�������ꂽ�u��
	bool isKeyDown(int key);
	//�L�[��������Ă����
	bool isKeyState(int key);
	//�L�[�������ꂽ�u��
	bool isKeyUp(int key);

private:
	IDirectInput8* m_pDinput;
	IDirectInputDevice8* m_pDevkeyborad;

	HRESULT mResult;
	//���̒l�Ƃ̘_���ςœ��͂����
	const int mInputNum = 0x80;

	//�L�[����
	BYTE mCurKey[256];
	BYTE mPreKey[256];
};

