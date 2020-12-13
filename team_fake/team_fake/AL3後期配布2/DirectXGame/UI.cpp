#include "UI.h"

UI::UI()
{
	count = 0;
}

void UI::Initialize()
{
	//体力ゲージ用
	Sprite::LoadTexture(0, L"Resources/white.png");//背面
	Sprite::LoadTexture(1, L"Resources/white.png");//本体1
	Sprite::LoadTexture(2, L"Resources/white.png");//本体2
	//Sprite::LoadTexture(3, L"");//前面
	
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
	if (subHp >= hp && count % 60 == 0)//減少がわかりやすいように
	{
		subHp -= 1;
	}
	if (subHp < hp)//回復したら
	{
		subHp = hp;
	}
	if (subHp <= 0)//0以下にならないよう
	{
		subHp = 0;
	}
	
	hpBottom->SetSize({ maxHp, 50 }); //体力の最大値を設定できるようにする
	hpMidle->SetSize({ subHp, 50 });   //現在の体力(減少前)
	hpTop->SetSize({ hp, 50 });   //現在の体力

}

void UI::HpDraw()
{
	hpBottom->Draw();
	hpMidle->Draw();
	hpTop->Draw();
	// hpGauge->Draw();
}
