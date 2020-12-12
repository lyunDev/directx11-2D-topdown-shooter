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
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
	output.uv = input.uv;
	return output;
}

Texture2D _sourceTex : register(t0);
Texture2D _dissolveMap : register(t1);
SamplerState _samp : register(s0);

cbuffer AlphaBuffer : register(b2)
{
    float _alpha;
}
cbuffer ColorBuffer : register(b3)
{
    float4 _addColor;
}
cbuffer DissolveBuffer : register(b4)
{
    float _dissolveAmount;
    float _fringeAmount;
}


float4 PS(PixelInput input) : SV_Target
{
    float4 dissolveColor;
    float dissolveMapValue;
    
    float4 color = _sourceTex.Sample(_samp,input.uv);
    

    dissolveColor = _dissolveMap.Sample(_samp, input.uv);
    dissolveMapValue = dissolveColor.x;
    
    if (dissolveMapValue <= _dissolveAmount)
    {
        color = float4(0, 0, 0, 0);
    }
    else if ((dissolveMapValue <= _dissolveAmount + _fringeAmount) && _dissolveAmount != 0)
    {
        if (color.a == 0.0f)
            return color;
        color = color + float4(10.0f, 0, 0, dissolveColor.a);
    }
    
    color.a *= _alpha;
    color += _addColor;
    return color;
}