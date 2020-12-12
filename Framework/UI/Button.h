#pragma once
#include "UIElement.h"

enum class BtnReactionType
{
	ColorChange = 0,
	SrvChange ,
	SizeChange,
};
class Button : public UIElement
{
public :
	Button(wstring filePath, Vector3 position, Vector3 size, function<void(void)> onButtonEvent, bool hasAnimation = false);
	Button(Vector3 position, Vector3 size, function<void(void)> onButtonEvent, bool hasAnimation = false);
	virtual ~Button();



public :
	void SetButtonUpEvent(function<void(void)> onButtonEvent);
	void SetButtonDownEvent(function<void(void)> onButtonEvent);
	void SetButtonPressEvent(function<void(void)> onButtonEvent);
	void SetChangeSRV(wstring filePath);

protected :
	virtual void OnMouseDown() override;
	virtual void OnMouseUp() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;

private :
	function<void(void)> buttonDownEvent = NULL;
	function<void(void)> buttonUpEvent = NULL;
	function<void(void)> buttonPressEvent = NULL;

	BtnReactionType btnReactionType = BtnReactionType::ColorChange;
	ID3D11ShaderResourceView * changeSRV;
};