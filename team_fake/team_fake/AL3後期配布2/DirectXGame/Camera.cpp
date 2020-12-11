#include "Camera.h"

Camera::Camera()
	:mViewport({}),
	mRect({}),
	matView(),
	matProjection(),
	eye(0,10,-100),
	target(0,0,0),
	up(0,1,0)
{

}

void Camera::Initialize(WinApp*winapp)
{
	//ビューポート設定
	mViewport.Width = winapp->GetWindowWidthSize();
	mViewport.Height = winapp->GetWindowHeightSize();
	mViewport.TopLeftX = 0;
	mViewport.TopLeftY = 0;
	mViewport.MaxDepth = 1.0;
	mViewport.MinDepth = 0;

	//シザー矩形
	mRect.top = 0;
	mRect.left = 0;
	mRect.right = mRect.left + winapp->GetWindowWidthSize();
	mRect.bottom = mRect.top + winapp->GetWindowHeightSize();

	//ビュー行列の生成
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));

	//透視投影変換
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)winapp->GetWindowWidthSize() / winapp->GetWindowHeightSize(),
		0.1f, 1000.0f
	);
}

void Camera::update()
{
	//ビュー行列の更新
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));
}

XMFLOAT3 Camera::getEyePos()
{
	return eye;
}

XMFLOAT3 Camera::getTargetPos()
{
	return target;
}

XMFLOAT3 Camera::getUpVec()
{
	return up;
}

void Camera::setEyePos(XMFLOAT3 eyePos)
{
	Camera::eye = eyePos;
	update();
}

void Camera::setTargetPos(XMFLOAT3 targetPos)
{
	Camera::target = targetPos;
	update();
}

void Camera::setUpVec(XMFLOAT3 upVec)
{
	Camera::up = upVec;
	update();
}

void Camera::moveEye(XMFLOAT3 eyePos)
{
	XMFLOAT3 moveEye = getEyePos();

	moveEye.x += eyePos.x;
	moveEye.y += eyePos.y;
	moveEye.z += eyePos.z;

	setEyePos(moveEye);
}

void Camera::moveTarget(XMFLOAT3 targetPos)
{
	XMFLOAT3 moveTarget = getTargetPos();

	moveTarget.x += targetPos.x;
	moveTarget.y += targetPos.y;
	moveTarget.z += targetPos.z;

	setTargetPos(moveTarget);
}

void Camera::moveUp(XMFLOAT3 upVec)
{
	XMFLOAT3 moveUp = getUpVec();

	moveUp.x += upVec.x;
	moveUp.y += upVec.y;
	moveUp.z += upVec.z;

	setUpVec(moveUp);
}

void Camera::cameraMove(XMFLOAT3 cameraMove)
{
	XMFLOAT3 moveEye = getEyePos();
	XMFLOAT3 moveTarget = getTargetPos();

	moveEye.x += cameraMove.x;
	moveEye.y += cameraMove.y;
	moveEye.z += cameraMove.z;

	moveTarget.x += cameraMove.x;
	moveTarget.y += cameraMove.y;
	moveTarget.z += cameraMove.z;

	setEyePos(moveEye);
	setTargetPos(moveTarget);
}

XMMATRIX Camera::GetmatView()
{
	return matView;
}

XMMATRIX Camera::GetmatProjection()
{
	return matProjection;
}

XMMATRIX Camera::GetinversView()
{
	XMMATRIX view= XMMatrixInverse(nullptr,matView);
	return view;
}

XMMATRIX Camera::GetinversProjection()
{
	XMMATRIX proj= XMMatrixInverse(nullptr, matProjection);
	return proj;
}
