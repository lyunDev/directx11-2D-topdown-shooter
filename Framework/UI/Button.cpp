#include "Framework.h"
#include "Button.h"
#include "ShaderBuffers/UIElementBuffer.h"

Button::Button(wstring filePath, Vector3 position, Vector3 size, function<void(void)> onButtonEvent, bool hasAnimation)
	: UIElement(filePath, position, size, hasAnimation)
{
	buttonUpEvent = onButtonEvent;
	SetUseMouseInteraction(true);
}

Button::Button(Vector3 position, Vector3 size, function<void(void)> onButtonEvent, bool hasAnimation)
	: UIElement(position, size, hasAnimation)
{
	buttonUpEvent = onButtonEvent;
	SetUseMouseInteraction(true);
}

Button::~Button()
{
}

void Button::SetChangeSRV(wstring filePath)
{
	Texture2D * tex = new Texture2D(filePath);
	changeSRV = tex->GetSRV();
}

void Button::OnMouseDown()
{
	if (buttonDownEvent != NULL)
		buttonDownEvent();
	switch (btnReactionType)
	{
	case BtnReactionType::ColorChange :
		// 테스트
		uiElementBuffer->SetAddColor(Color(-0.2f, -0.2f, -0.2f, 0));
		break;
	case BtnReactionType::SrvChange:
		if (changeSRV == nullptr)
			break;
		SetSRV(changeSRV);
		break;
	default:
		break;
	}

}

void Button::OnMouseUp()
{
	if(buttonUpEvent != NULL)
		buttonUpEvent();
	switch (btnReactionType)
	{
	case BtnReactionType::ColorChange:
		// 테스트
		uiElementBuffer->SetAddColor(Color(0, 0, 0, 0));
		break;
	case BtnReactionType::SrvChange:
		SetSRV(GetOriginalSRV());
		break;
	default:
		break;
	}
	
}

void Button::OnEnable()
{
}

void Button::OnDisable()
{
}
