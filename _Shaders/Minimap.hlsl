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

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp,input.uv);
    if(input.uv.x < 0.01f)
        return float4(1, 1, 1, 1);
    if(input.uv.x > 0.99f)
        return float4(1, 1, 1, 1);
    if(input.uv.y < 0.01f)
        return float4(1, 1, 1, 1);
    if(input.uv.y > 0.99f)
        return float4(1, 1, 1, 1);
    color.rgb = dot(color.rgb, float3(0.3, 0.59, 0.11));
    color.a = 1.0;
    return color;
}