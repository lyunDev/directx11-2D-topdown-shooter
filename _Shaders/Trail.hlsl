//VertexTexture

struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
    float4 normal : NORMAL;
};


struct PixelInput
{
    float4 position : SV_POSITION; // System Value Position - Has specific meaning to the pipeline!
    float3 normal : TEXCOORD0;
    float2 uv : TEXCOORD1;
    float age : TEXCOORD2;
    float4 acceleration : TEXCOORD3;
    float4 color : TEXCOORD4;
};


cbuffer WorldBuffer : register(b0)
{    matrix _world;
};

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
}

cbuffer GeoBuffer : register(b2)
{
    float age;
    float3 position;
    float4 acceleration;
    float4 color;
};
PixelInput VS(VertexInput input)
{
    PixelInput output;
//	matrix worldViewProj = mul(mul(world, view), projection);
	//output.position = mul(float4(input.position, 1.0f), worldViewProj);
    output.position = float4(position / 10, 1);
    output.normal = input.normal;
    output.uv = input.uv;
    output.age = age;
    output.acceleration = acceleration;
    output.color = color;
    return output;

}


float4 PS(PixelInput input) : SV_TARGET
{
    float u = input.uv.x;
    float v = input.uv.y;
    float opacity = v;
	input.color.w *= (input.uv.y + input.color.w);
	input.color.w /= 2;
    return input.color;
}

struct GSInput
{
    float4 position : SV_POSITION;
    float3 normal : TEXCOORD0;
    float2 uv : TEXCOORD1;
    float age : TEXCOORD2;
    float4 acceleration : TEXCOORD3;
};

struct GSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};


void createParticle(GSOutput input, inout TriangleStream<GSOutput> output, float r, float4 nextPosition)
{

    matrix worldViewProj = mul(mul(_world, _view), _projection);
    float4 v[4];
    float4 position = input.position;
    v[0] = position; // +float4(r, -r, 0.0f, 0.0f);
    v[1] = v[0] - float4(0, r, 0, 0);
    v[2] = nextPosition; //(position + nextPosition)/2;//+ float4(-r/3, -r/3, 0.0f, 0.0f);
    v[3] = nextPosition - float4(0, r - 0.001, 0, 0);

    float2 quadUVs[4] =
    {
        float2(1.0f, 0.0f),
		float2(1.0f, 1.0f),
		float2(0.0f, 1.0f),
		float2(0.0f, 0.0f),
    };

    GSOutput element = input;
    for (uint i = 0; i < 4; i++)
    {
        element.position = mul(v[i], worldViewProj);
        element.uv = quadUVs[i];
        output.Append(element);
    }
//	output.RestartStrip();
}


[maxvertexcount(100)]
void main(
	point GSInput input[1],
	inout TriangleStream<GSOutput> output
	)
{

    matrix worldViewProj = mul(mul(_world, _view), _projection);
    GSOutput element;
    element.position = input[0].position;
    element.position.x -= 0.1;
    element.position.y -= 0.02;
    element.uv = float2(1, 1);
    float t = input[0].age;
    float opacity = 1;
    float4 nextPosition = element.position;
    float r = 0.04;
    float v = input[0].acceleration.y;
    float sign = v / abs(v);
    for (uint i = 0; i < 50; ++i)
    {
        float a = t - input[0].age;

        nextPosition.y = ((nextPosition.y) - (0.5 * v * a)); // +(input[0].position.y);
        nextPosition.x -= (r * 2); //8=;
        createParticle(element, output, r, nextPosition);
        element.position = nextPosition;
        element.color = float4(0, 1, 1, 1.5 - abs(nextPosition.x - input[0].position.x));
        r -= 0.001;
        t += 0.001;
    }
}