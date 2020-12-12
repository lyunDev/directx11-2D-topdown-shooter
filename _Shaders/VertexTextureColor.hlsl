//VertexTexture

struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
    float4 color : COLOR;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float4 color : COLOR;
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
    output.color = input.color;
	return output;
}

cbuffer TileMapBuffer : register(b0)
{
    float3 _mPos;
}

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
   
    float4 color = _sourceTex.Sample(_samp,input.uv);
    
    float x = _mPos.x / 1280.0f;
    float y = 1 - _mPos.y / 720.0f;
    if(input.uv.x < x + 0.1f
        && input.uv.x > x - 0.1f
        && input.uv.y > y - (0.1f * 1280.0f / 720.f)
        && input.uv.y < y + (0.1f * 1280.0f / 720.f))
        color += float4(1, 0, 0, 0);
        
    
    return clamp(color + input.color, float4(0, 0, 0, 0), float4(1, 1, 1, 1));
}