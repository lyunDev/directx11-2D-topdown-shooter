#pragma once


class Camera : public SingletonBase<Camera>
{
public :
	friend class SingletonBase<Camera>;

	void Update();
	void Render();

	void Move();
	void UpdateView();

	void UnProjection(Vector3 * out, Vector3 source, Matrix world);

	void SetTarget(Vector3 * position);

	Vector3 GetPos()
	{
		return position;
	}
private :
	Camera();
	~Camera();


	VPBuffer * vpb = nullptr;
	D3DXMATRIX view, proj;

	Vector3 position = Values::ZeroVec3;

	Vector3 * targetPos = nullptr;
	float cameraSpeed = 100.0f;

public :
	void Shake(float shakeDuration, float shakeAmount = 0.7f, float decreaseFactor = 1.0f);
private :
	void ShakeUpdate();
private :
	float shakeDuration = 0;
	float shakeAmount = 0;
	float decreaseFactor = 0;
	Vector3 originPos;
};