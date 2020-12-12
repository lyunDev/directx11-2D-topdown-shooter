#pragma once

#include "IntegratedRect.h"
class Animator;
class AnimationRect : public IntegratedRect
{
	friend class GameObject;
public :
	AnimationRect(Transform * transform);
	~AnimationRect();

	void Update();
	void Render();


	void SetAnimator(Animator* animator) { this->animator = animator; }
private : 
	class Animator* animator = nullptr;

	ID3D11SamplerState * point[2];
	ID3D11BlendState* blend[2];
};