#pragma once


class TMapDemo : public IObject
{
public :

	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void GUI() override;

private :
	class TMap * tm = nullptr;
};