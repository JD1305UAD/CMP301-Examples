// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader

Texture2D texture1 : register(t0);
SamplerState heightSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct InputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct OutputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

cbuffer timeBuffer : register(b1)
{
	float timer;
	float amplitude;
	float frequency;
	float speed;
};

//cbuffer sineBuffer : register(b2)
//{
//	float amplitude;
//	float frequency;
//	float speed;
//	float3 padding;
//};

OutputType main(InputType input)
{
	OutputType output;

	float4 offset = texture1.SampleLevel(heightSampler, input.tex, 0);

	input.position.y = offset.xz * 15;

	//float twopi = 6.28f;
	//float k = twopi / frequency;

	//offset position based on sine wave
	//input.position.y= sin(input.position.x + timer);
	
	////offset position based on sine wave
	//input.position.y = sin(input.position.x + (timer * speed));
	//input.position.y *= amplitude;

	//input.position.x *= frequency;

	////input.position.z = -cos(timer);

	////modify normals
	//input.normal.x = (1 - cos(input.position.x + (timer * speed)));
	//input.normal.y = abs(cos(input.position.x + (timer * speed)));

	//modify normals
	//input.normal.x = amplitude -cos(speed * input.position.x + timer);
	//input.normal.y = amplitude * sin(k * input.normal.x);
		
		//abs(cos(input.position.x + timer)); 

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only and normalise.
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	return output;
}