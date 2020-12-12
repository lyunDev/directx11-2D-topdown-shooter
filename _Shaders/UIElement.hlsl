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
    //output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
	output.uv = input.uv;
	return output;
}


cbuffer UIElementBuffer : register(b5)
{
    float4 _addColor;
    float _processAmount;
}
cbuffer AlphaBuffer : register(b2)
{
    float _alpha;
}
Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color;
    if (input.uv.x > _processAmount)
        return float4(0, 0, 0, 0);
    color =  _sourceTex.Sample(_samp, input.uv);
    color.a = color.a * _alpha;
    return color;
}