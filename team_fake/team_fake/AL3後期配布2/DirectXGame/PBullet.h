#pragma once
#include "Enemy.h"

class Player;
class Enemy;

class PBullet
{
public:

	void Initialize(XMFLOAT3 pos, Object3d* bullet);

	void Update(Player*player, MouseInput* mouse,Camera* camera,WinApp* winApp) ;

	void Move(Player* player, MouseInput* mouse, Camera* camera, WinApp* winApp);

	void Draw();

	void SetBoolShot(bool value);

	bool Collisions(Enemy* Enemy);

	Object3d GetObjectShape();

	XMFLOAT3 GetPosition();

	void Release();

private:
	XMFLOAT3 position;
	Object3d* pbObj;
	Collision* col;

	float speed;
	float distX;
	float distY;
	float mag;
	bool shot;
	bool once;//àÍâÒÇæÇØåƒÇ—èoÇ∑ÇΩÇﬂÇÃÇ‡ÇÃ

};