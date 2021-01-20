#pragma once
#include "Sprite.h"
#include <DirectXMath.h>


class UI
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;


public:

	UI();

	void Initialize();

	void InitHP(float hp);

	void HpGauge(float hp);

	void HpDraw();

	void ShotDistance(XMFLOAT2 dist);

	void ShotDistDraw();

private:
	Sprite* hpBottom = nullptr;
	Sprite* hpMidle = nullptr;
	Sprite* hpTop = nullptr;
	Sprite* hpGauge = nullptr;
	Sprite* shotDist = nullptr;

	XMFLOAT2 shotPos;

	float maxHp=0;
	float subHp=0;
	int count;
};