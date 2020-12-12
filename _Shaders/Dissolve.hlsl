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
cbuffer DissolveBuffer : register(b2)
{
    float dissolveAmount;
    float fringeAmount;
    float2 padding;
}

Texture2D dissolveTexture : register(t0);
Texture2D dissolveMap : register(t1);
SamplerState _samp : register(s0);



float4 PS(PixelInput input) :SV_TARGET
{
   // return float4(1, 0, 0, 1);
    
    float4 textureColor;
    float4 dissolveColor;
    float dissolveMapValue;
    
    textureColor = dissolveTexture.Sample(_samp, input.uv);
    dissolveColor = dissolveMap.Sample(_samp, input.uv);
    dissolveMapValue = dissolveColor.x;
    
    if(dissolveMapValue <= dissolveAmount)
    {
        textureColor = float4(0, 0, 0, 0);
    }
    else if((dissolveMapValue <= dissolveAmount + fringeAmount) && dissolveAmount != 0)
    {
        if( textureColor.a == 0.0f)
            return textureColor;
        textureColor = textureColor + float4(10.0f, 0, 0, dissolveColor.a);
    }
    return textureColor;
}

