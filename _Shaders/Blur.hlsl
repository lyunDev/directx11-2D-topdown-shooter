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


cbuffer TextureBuffer : register(b0)
{
    float2 _imageSize;
    int _blurCount; // 높을수록 블러가 커지고 흐려짐
}


Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, input.uv);

    float2 arr[8] =
    {
        float2(-1, -1), float2(0, -1), float2(1, -1),
        float2(-1, 0),                float2(1, 0),
        float2(-1, 1), float2(0, 1), float2(1, 1)
    };
    
    for (int blur = 1; blur < _blurCount; blur++)
    {
        for (int i = 0; i < 8; i++)
        {
            float x = arr[i].x * blur/ _imageSize.x;
            float y = arr[i].r * blur / _imageSize.y;
        
            float2 uv = input.uv + float2(x, y);
            color += _sourceTex.Sample(_samp, uv);
        }
    }
    color /= 8 * (_blurCount - 1) + 1;
    

    return color;
}