#pragma once


class CollisionDemo : public IObject
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

	class Rect* r1 = nullptr;
	class Rect* r2 = nullptr;

	vector<function<void()>> switchPtrs;
	bool  isOn = true;
};
