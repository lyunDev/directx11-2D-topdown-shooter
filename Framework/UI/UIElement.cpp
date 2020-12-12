#include "Framework.h"
#include "UIElement.h"
#include "Utilities/ShaderCreator.h"
#include "Utilities/Animator.h"
#include "Utilities/TextureCreator.h"
#include "ShaderBuffers/UIElementBuffer.h"
#include "Game/Transform.h"
UIElement::UIElement(wstring filePath, Vector3 position, Vector3 size, bool hasAnimation)
	: GameObject(position, size, 0, hasAnimation)
{
	
	uiElementBuffer = new UIElementBuffer();

	Texture2D * tex = new Texture2D(filePath);
	SetSRV(tex->GetSRV());

	SetShader(ShaderPath + L"UIElement.hlsl");
	SetObjectLayer(ObjectLayer::UI);
	SetRenderLayer(RenderLayer::UI);

}

UIElement::UIElement(Vector3 position, Vector3 size, bool hasAnimation)
	: GameObject(position, size, 0, hasAnimation)
{
	uiElementBuffer = new UIElementBuffer();

	SetShader(ShaderPath + L"UIElement.hlsl");

	SetObjectLayer(ObjectLayer::UI);
	SetRenderLayer(RenderLayer::UI);
}

UIElement::~UIElement()
{
	SAFE_DELETE(uiElementBuffer);
}


void UIElement::OnUpdate()
{
	MouseInteract();
}

void UIElement::OnRender()
{
	uiElementBuffer->SetPSBuffer(5);
}

void UIElement::MouseInteract()
{
	if (!useMouseInteraction)
		return;
	if (CheckMouseTouched())
	{
		if (Mouse::Get()->Up(0))
		{
			OnMouseUp();
		}
		if(Mouse::Get()->Down(0))
		{
			OnMouseDown();
		}
		
		if (Mouse::Get()->Press(0))
		{
			OnMousePress();
		}
	}

}


bool UIElement::CheckMouseTouched()
{
	Vector3 leftTop = Vector3
	(
		transform->position.x - transform->size.x * 0.5f,
		transform->position.y + transform->size.y * 0.5f,
		0
	);
	Vector3 rightBottom = Vector3
	(
		transform->position.x + transform->size.x * 0.5f,
		transform->position.y - transform->size.y * 0.5f,
		0
	);
	Vector3 mousePos = Mouse::Get()->GetPosition();
	if (mousePos.x > leftTop.x
		&& mousePos.y < leftTop.y
		&& mousePos.x <rightBottom.x
		&& mousePos.y > rightBottom.y)
		return true;
	return false;
}

