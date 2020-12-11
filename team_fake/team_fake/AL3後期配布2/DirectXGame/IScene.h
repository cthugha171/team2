#pragma once
#include "Scene.h"
#include "Direct.h"
#include "Input.h"
#include "MouseInput.h"
#include "Camera.h"
#include "WinApp.h"
#include "DirectXCommon.h"


class IScene
{
public:
	virtual void Initialize(DirectXCommon* directXInit) {}//������

	virtual void Update(Input*input, MouseInput* mouse, Camera* camera, WinApp* winApp) {}//�X�V

	virtual void Draw() {}//�`��

	virtual void Delete() {}//�F�X�폜

	//�V�[���Ǘ�
	bool IsEnd() {}//�I���`�F�b�N
	Scene Next() {}//���̃V�[��

};

