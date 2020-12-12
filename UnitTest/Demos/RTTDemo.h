#pragma once


class RTTDemo : public IObject
{
public :
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void GUI() override;

private :
	class RenderTexture * rtt = nullptr;
	class Rect* r = nullptr; // 그냥 정상적으로 찍고 
	class Rect* r2 = nullptr;
	class Rect* r3 = nullptr;
	
	class TextureRect* rt2 = nullptr; // <- RTT한 이미지를 여기에 찍고  (minimap)


	class TextureRect* rt1 = nullptr; // greyscale?

};