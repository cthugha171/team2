#pragma once
#include <d3d12.h>
#include <DirectXMath.h>

#include "WinApp.h"

using namespace DirectX;
class Camera
{
public:
	Camera();
	void Initialize(WinApp*winapp);
	void update();

	XMFLOAT3 getEyePos();
	XMFLOAT3 getTargetPos();
	XMFLOAT3 getUpVec();

	void setEyePos(XMFLOAT3 eyePos);
	void setTargetPos(XMFLOAT3 targetPos);
	void setUpVec(XMFLOAT3 upVec);

	void moveEye(XMFLOAT3 eyePos);
	void moveTarget(XMFLOAT3 targetPos);
	void moveUp(XMFLOAT3 upVec);

	void cameraMove(XMFLOAT3 cameraMove);

	XMMATRIX GetmatView();

	XMMATRIX GetmatProjection();

	XMMATRIX GetinversView();

	XMMATRIX GetinversProjection();

private:
	//�r���[�|�[�g
	D3D12_VIEWPORT mViewport;
	//�V�U�[��`
	D3D12_RECT mRect;

	//�r���[�s��
	XMMATRIX matView;
	//���e�s��
	XMMATRIX matProjection;
	//���_���W
	XMFLOAT3 eye;
	//�����_���W
	XMFLOAT3 target;
	//������x�N�g��
	XMFLOAT3 up;
};

