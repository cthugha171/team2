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
	//ビューポート
	D3D12_VIEWPORT mViewport;
	//シザー矩形
	D3D12_RECT mRect;

	//ビュー行列
	XMMATRIX matView;
	//投影行列
	XMMATRIX matProjection;
	//視点座標
	XMFLOAT3 eye;
	//注視点座標
	XMFLOAT3 target;
	//上方向ベクトル
	XMFLOAT3 up;
};

