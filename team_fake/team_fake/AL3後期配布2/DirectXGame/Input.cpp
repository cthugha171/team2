#include "Input.h"



Input::Input():
m_pDinput(nullptr),
m_pDevkeyborad(nullptr),
mCurKey(),
mPreKey(),
mResult(NULL)
{
	
}


Input::~Input()
{
}

void Input::initialize(WinApp* winapp)
{
	//DirectInput�I�u�W�F�N�g�̐���
	mResult = DirectInput8Create(winapp->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDinput, nullptr);
	//�L�[�{�[�h�f�o�C�X�̐���
	mResult = m_pDinput->CreateDevice(GUID_SysKeyboard, &m_pDevkeyborad, NULL);
	//�f�[�^���͂̌^���̃Z�b�g
	m_pDevkeyborad->SetDataFormat(&c_dfDIKeyboard);  //�W���`��
	//�r���I����̃��x���Z�b�g
	//�t���O�ɂ���   DISCL_FOREGROUND�F��ʂ���O�ɂ���ꍇ�̂ݓ��͂��󂯕t����    DISCL_NONEXCLUSIVE�F�f�o�C�X�����̃A�v�������Ő�L���Ȃ�    DISCL_NOWINKEY�FWindows�L�[�𖳌��ɂ���
	m_pDevkeyborad->SetCooperativeLevel(winapp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

}

void Input::update()
{
	//1�t���[���O�̃L�[���X�V
	for (int i = 0; i < 256; i++)
	{
		mPreKey[i] = mCurKey[i];
	}
	//���ׂẲ��z�L�[�̏�Ԃ�ێ����� 256 �o�C�g�̔z��ւ̃|�C���^���w�肷��B
	mResult = m_pDevkeyborad->Acquire();
	mResult = m_pDevkeyborad->GetDeviceState(sizeof(mCurKey), mCurKey);
}

//�L�[�������ꂽ�u��
bool Input::isKeyDown(int key)
{
	return (mCurKey[key] & mInputNum) && !(mPreKey[key] & mInputNum);
}
//�L�[��������Ă����
bool Input::isKeyState(int key)
{
	return (mCurKey[key] & mInputNum) && (mPreKey[key] & mInputNum);
}
//�L�[�������ꂽ�u�� 
bool Input::isKeyUp(int key)
{
	return !(mCurKey[key] & mInputNum) && (mPreKey[key] & mInputNum);
}
