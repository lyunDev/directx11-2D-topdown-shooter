#pragma once
#include "Game/GameObject.h"
#include "Utilities/Animator.h"
#include "ShaderBuffers/UIElementBuffer.h"
class UIElement : public GameObject
{
public :
	UIElement(wstring filePath, Vector3 position, Vector3 size, bool hasAnimation);
	UIElement(Vector3 position, Vector3 size, bool hasAnimation);
	virtual ~UIElement();

	UIElementBuffer * GetUIElementBuffer()
	{
		return uiElementBuffer;
	}
	
private :
	void MouseInteract();
	bool CheckMouseTouched();
protected :

	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnMouseDown() {}
	virtual void OnMouseUp() {}
	virtual void OnMousePress() {}

	void SetUseMouseInteraction(bool useMouseInteraction)
	{
		this->useMouseInteraction = useMouseInteraction;
	}
private :


protected :
	class UIElementBuffer * uiElementBuffer;
private :
	bool useMouseInteraction = false;
	float processAmount = 0; // 0 ~ 1
};