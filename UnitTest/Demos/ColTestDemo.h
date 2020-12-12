#pragma once

enum class Direction
{
	Left = 0, Right, Down, Up
};
class ColTestDemo : public IObject
{
public:


	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void GUI() override;

private:

	class Rect* r1 = nullptr;
	class Rect* r2 = nullptr;

	class Rect* upStage = nullptr;
	class Rect* rightStage = nullptr;
	class Rect* leftStage = nullptr;
	class Rect* downStage = nullptr;

	Direction direction = Direction::Left;
};
