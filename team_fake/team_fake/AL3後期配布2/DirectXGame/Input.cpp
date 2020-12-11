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
	//DirectInputオブジェクトの生成
	mResult = DirectInput8Create(winapp->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDinput, nullptr);
	//キーボードデバイスの生成
	mResult = m_pDinput->CreateDevice(GUID_SysKeyboard, &m_pDevkeyborad, NULL);
	//データ入力の型式のセット
	m_pDevkeyborad->SetDataFormat(&c_dfDIKeyboard);  //標準形式
	//排他的制御のレベルセット
	//フラグについて   DISCL_FOREGROUND：画面が手前にある場合のみ入力を受け付ける    DISCL_NONEXCLUSIVE：デバイスをこのアプリだけで専有しない    DISCL_NOWINKEY：Windowsキーを無効にする
	m_pDevkeyborad->SetCooperativeLevel(winapp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

}

void Input::update()
{
	//1フレーム前のキーを更新
	for (int i = 0; i < 256; i++)
	{
		mPreKey[i] = mCurKey[i];
	}
	//すべての仮想キーの状態を保持する 256 バイトの配列へのポインタを指定する。
	mResult = m_pDevkeyborad->Acquire();
	mResult = m_pDevkeyborad->GetDeviceState(sizeof(mCurKey), mCurKey);
}

//キーが押された瞬間
bool Input::isKeyDown(int key)
{
	return (mCurKey[key] & mInputNum) && !(mPreKey[key] & mInputNum);
}
//キーが押されている間
bool Input::isKeyState(int key)
{
	return (mCurKey[key] & mInputNum) && (mPreKey[key] & mInputNum);
}
//キーが離された瞬間 
bool Input::isKeyUp(int key)
{
	return !(mCurKey[key] & mInputNum) && (mPreKey[key] & mInputNum);
}
