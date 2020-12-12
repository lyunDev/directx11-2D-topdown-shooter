#pragma once


class RenderTexture
{
public :
	RenderTexture();
	~RenderTexture();

	void RenderToTexture(); // RTT기법 (Render To Texture 기법)

	ID3D11ShaderResourceView * GetSRV() { return srv; }
private :
	ID3D11Texture2D * texture = nullptr;
	ID3D11RenderTargetView * rtv = nullptr;
	ID3D11ShaderResourceView* srv = nullptr;

	Color clearColor = Color(0.63f, 0.8f, 0.63f, 1);

};