#include "UI.h"

UI::UI()
{
	count = 0;
}

void UI::Initialize()
{
	//�̗̓Q�[�W�p
	Sprite::LoadTexture(0, L"Resources/white.png");//�w��
	//Sprite::LoadTexture(1, L"Resources/white.png");//�{��1
	//Sprite::LoadTexture(2, L"Resources/white.png");//�{��2
	Sprite::LoadTexture(3, L"Resources/hpGauge.png");//�O��
	
	hpBottom = Sprite::Create(0, { 50,50 }, { 0.5f,0.5f,0.5f,1 });
	hpMidle = Sprite::Create(0, { 50,50 }, { 1.0f,0.0f,0.0f,1 });
	hpTop = Sprite::Create(0, { 50,50 }, { 0.0f,1.0f,0.0f,1 });
	hpGauge = Sprite::Create(3, { 50,50 });
}

void UI::InitHP(float hp)
{
	maxHp = hp;
	subHp = hp;
}

void UI::HpGauge(float hp)
{
	if (subHp >= hp && count % 60 == 0)//�������킩��₷���悤��
	{
		subHp -= 1;
	}
	if (subHp < hp)//�񕜂�����
	{
		subHp = hp;
	}
	if (subHp <= 0)//0�ȉ��ɂȂ�Ȃ��悤
	{
		subHp = 0;
	}
	
	hpBottom->SetSize({ maxHp, 50 }); //�̗͂̍ő�l��ݒ�ł���悤�ɂ���
	hpMidle->SetSize({ subHp, 50 });   //���݂̗̑�(�����O)
	hpTop->SetSize({ hp, 50 });   //���݂̗̑�
	hpGauge->SetSize({ maxHp,50 });


}

void UI::HpDraw()
{
	hpBottom->Draw();
	hpMidle->Draw();
	hpTop->Draw();
	hpGauge->Draw();
}
