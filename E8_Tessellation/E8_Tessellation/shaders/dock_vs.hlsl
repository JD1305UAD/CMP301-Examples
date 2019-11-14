// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader

Texture2D displacementTex : register(t0);
SamplerState heightSampler0 : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix lightViewMatrix;
	matrix lightProjectionMatrix;
};

struct InputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	uint vertexID : SV_VERTEXID;
};

struct OutputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float4 depthPosition : TEXCOORD2;
	float4 lightViewPos : TEXCOORD3;
};


OutputType main(InputType input)
{
	OutputType output;

	//float4 offset = displacementTex.SampleLevel(heightSampler0, input.tex, 0);
	float4 offset;

	// Store the texture coordinates for the pixel shader.
	//output.tex = input.tex;

	//front
	if (input.vertexID < 2400)
	{
		output.tex = float2(input.tex.x * 3, input.tex.y * 1);
		//offset = displacementTex.SampleLevel(heightSampler0, output.tex, 0);
		//input.position.z -= offset.x * 0.01;
	}
	//back
	else if (input.vertexID > 2399 && input.vertexID < 4800)
	{
		output.tex = float2(input.tex.x * 3, input.tex.y * 1);
		//offset = displacementTex.SampleLevel(heightSampler0, output.tex, 0);
		//input.position.z += offset.x * 0.01;
	}
	//right
	else if (input.vertexID > 4799 && input.vertexID < 7200)
	{
		output.tex = float2(input.tex.x * 25, input.tex.y * 1);
		//offset = displacementTex.SampleLevel(heightSampler0, output.tex, 0);
		//input.position.x += offset.x * 0.1;
	}
	//left
	else if (input.vertexID > 7199 && input.vertexID < 9600)
	{
		output.tex = float2(input.tex.x * 25, input.tex.y * 1);
		//offset = displacementTex.SampleLevel(heightSampler0, output.tex, 0);
		//input.position.x -= offset.x * 0.1;
	}
	//top
	else if (input.vertexID > 9599 && input.vertexID < 12000)
	{
		output.tex = float2(input.tex.x * 3, input.tex.y * 25);
		//offset = displacementTex.SampleLevel(heightSampler0, output.tex, 0);
		//input.position.y += offset.x;
	}
	//bottom
	else if (input.vertexID > 11999 && input.vertexID < 14400)
	{
		output.tex = float2(input.tex.x * 3, input.tex.y * 25);
		//offset = displacementTex.SampleLevel(heightSampler0, output.tex, 0);
		//input.position.y -= offset.x;
	}


	//output.tex = input.tex * 3; // 3x3
	//output.tex = float2(input.tex.x * 3, input.tex.y * 25);


	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Calculate the position of the vertice as viewed by the light source.
	output.lightViewPos = mul(input.position, worldMatrix);
	output.lightViewPos = mul(output.lightViewPos, lightViewMatrix);
	output.lightViewPos = mul(output.lightViewPos, lightProjectionMatrix);

	// Calculate the normal vector against the world matrix only and normalise.
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);


	output.depthPosition = output.position;

	return output;
}