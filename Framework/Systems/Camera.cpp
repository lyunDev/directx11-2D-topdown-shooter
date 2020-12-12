#include "Framework.h"
#include "Camera.h"

void Camera::Update()
{
	Move();
	ShakeUpdate();
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move()
{
	/*if (Keyboard::Get()->Press(VK_LSHIFT))
	{
		if (Keyboard::Get()->Press('W'))
			position.y += cameraSpeed * Time::Delta();
		else if (Keyboard::Get()->Press('S'))
			position.y -= cameraSpeed * Time::Delta();

		if (Keyboard::Get()->Press('A'))
			position.x -= cameraSpeed * Time::Delta();
		else if (Keyboard::Get()->Press('D'))
			position.x += cameraSpeed * Time::Delta();
	}*/
	if (targetPos != nullptr)
	{
		Vector3 result;
		Vector3 target;
		target.x = targetPos->x - WinMaxWidth / 2;
		target.y = targetPos->y - WinMaxHeight / 2;
		D3DXVec3Lerp(&result, &position, &target, Time::Delta());
		position.x = result.x;
		position.y = result.y;
	}
	UpdateView();
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH(&view, &position, &(position + Values::FwdVec), &Values::UpVec);
	vpb->SetView(view);
}

// source :: ¸¶¿ì½º ÁÂÇ¥
void Camera::UnProjection(Vector3 * out, Vector3 source, Matrix world)
{
	/*
		NDC -> Screen Space
		x = (NDC.x + 1) * viewport.width * 0.5f + viewport.topleftX
		y = (1 - NDC.y) * viewport.height * 0.5f + viewport.topleftY	
	*/

	Vector3 position = source;

	out->x = (position.x * 2.0f / WinMaxWidth) - 1.0f;
	out->y = (position.y * 2.0f / WinMaxHeight) - 1.0f;
	out->z = position.z;

	Matrix wvp = world * view * proj;
	D3DXMatrixInverse(&wvp, nullptr, &wvp);
	// local * world * view * projection * 1 / wvp
	// local 

	D3DXVec3TransformCoord(out, out, &wvp);
}

void Camera::SetTarget(Vector3 * position)
{
	targetPos = position;
}

Camera::Camera()
{
	vpb = new VPBuffer();

	D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 1), &D3DXVECTOR3(0, 1, 0));
	//D3DXMatrixOrthoLH(&proj, WinMaxWidth, WinMaxHeight, 0, 1);
	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, (float)WinMaxWidth, 0.0f, (float)WinMaxHeight, 0, 1);
	vpb->SetView(view);
	vpb->SetProj(proj);

}

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}

void Camera::Shake(float shakeDuration, float shakeAmount, float decreaseFactor)
{
	this->shakeDuration = shakeDuration;
	this->shakeAmount = shakeAmount;
	this->decreaseFactor = decreaseFactor;
	originPos = position;
}

void Camera::ShakeUpdate()
{
	if (shakeDuration > 0)
	{
		position = position + Vector3(
			DxMath::ReliableRandom(-1, 1), 
			DxMath::ReliableRandom(-1, 1), 0) 
			* shakeAmount;

		shakeDuration -= Time::Delta() * decreaseFactor;
	}
	else
	{
		shakeDuration = 0;
	}
}
