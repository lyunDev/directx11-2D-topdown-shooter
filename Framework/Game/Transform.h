#pragma once

class Transform
{
public :
	Vector3 position;
	Vector3 size;
	float rotation;

public :
	void Rotate(float radian)
	{
		Matrix rotationMat;
		Matrix positionMat;
		D3DXMatrixTranslation(&positionMat, position.x, position.y, position.z);
		D3DXMatrixRotationZ(&rotationMat, radian);
		Matrix result = positionMat *rotationMat;
		D3DXVec3TransformCoord(&position, &Vector3(0, 0, 0), &result);

	}

	Vector3 GetLocalUpDirection()
	{
		Vector3 localUp;
		Matrix positionMat;
		Matrix rotationMat;
		D3DXMatrixTranslation(&positionMat, 0,1, 0);
		D3DXMatrixRotationZ(&rotationMat, D3DXToRadian( rotation));
		Matrix result = positionMat * rotationMat;
		D3DXVec3TransformCoord(&localUp, &Vector3(0, 0, 0), &result);
		return localUp;
	}
};