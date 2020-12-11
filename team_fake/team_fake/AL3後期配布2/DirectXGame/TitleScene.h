#pragma once
#include "IScene.h"
#include "Sprite.h"
#include "DirectXCommon.h"//#include "DirecXInit.h"
#include "Input.h"
#include "Model.h"
#include "Object3d.h"

class TitleScene : public IScene
{
public:
	void Initialize(DirectXCommon* directXInit);

	void Update(Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp);

	void Draw(DirectXCommon* directXInit);

	void Delete();
private:
	Model* ground;
	Object3d* objground;
};
