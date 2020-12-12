//VertexTexture

struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
};

cbuffer WorldBuffer : register(b0)
{
    matrix _world;
};

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
}
PixelInput VS(VertexInput input)
{
	PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _projection);
    
	output.uv = input.uv;
	return output;
}


cbuffer ProgressBuffer : register(b6)
{
    float _processAmount;
}

Texture2D _progressTex : register(t0);
Texture2D _backgroundTex : register(t3);

SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
   
    if(input.uv.x > _processAmount)
        return _backgroundTex.Sample(_samp, input.uv);
    return _progressTex.Sample(_samp, input.uv);
  
}