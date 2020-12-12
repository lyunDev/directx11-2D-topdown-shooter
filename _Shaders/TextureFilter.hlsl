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
SamplerState _samp : register(s0);
cbuffer FilterType : register(b2)
{
    uint1 _filterType;
    uint3 _padding;
}

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp,input.uv);
    // grayscale 
    if(_filterType == 0)
    {
        color.rgb = dot(color.rgb, float3(0.3, 0.59, 0.11));
        color.a = 1.0;
    }
    else if (_filterType == 1)
    {
        float4 sepia;
        sepia.a = color.a;
        sepia.r = dot(color.rgb, float3(0.393f, 0.769f, 0.189f));
        sepia.g = dot(color.rgb, float3(0.349f, 0.686f, 0.168f));
        sepia.b = dot(color.rgb, float3(0.272f, 0.534f, 0.131f));
        color = sepia;
    }
    return color;
}