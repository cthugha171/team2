#pragma once
#include "Sprite.h"

class UI
{
public:

	UI();

	void Initialize();

	void InitHP(float hp);

	void HpGauge(float hp);

	void HpDraw();

private:
	Sprite* hpBottom = nullptr;
	Sprite* hpMidle = nullptr;
	Sprite* hpTop = nullptr;
	Sprite* hpGauge = nullptr;
	float maxHp=0;
	float subHp=0;
	int count;
};