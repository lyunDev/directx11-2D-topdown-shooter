#pragma once

class IObject
{
public :
	virtual void Init() = 0;
	virtual void Destroy() = 0;

	virtual void Update() = 0;

	virtual void PreRender() = 0;
	virtual void Render() = 0;
	

	virtual void GUI() = 0;
};