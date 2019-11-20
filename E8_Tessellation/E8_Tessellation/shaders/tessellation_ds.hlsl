// Tessellation domain shader
// After tessellation the domain shader processes the all the vertices


Texture2D displacementTex : register(t0);
//Texture2D normTex : register(t1);


SamplerState heightSampler0 : register(s0);
//SamplerState normSampler : register(s1);

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct ConstantOutputType
{
    float edges[4] : SV_TessFactor;
    float inside[2] : SV_InsideTessFactor;
};

struct InputType
{
    float3 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct OutputType
{
    float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
};

[domain("quad")]
OutputType main(ConstantOutputType input, float2 uvwCoord : SV_DomainLocation, const OutputPatch<InputType, 4> patch)
{
    float3 vertexPosition;
    OutputType output;

	float2 t1 = lerp(patch[0].tex, patch[1].tex, uvwCoord.y);
	float2 t2 = lerp(patch[2].tex, patch[3].tex, uvwCoord.y);
	float2 texPosition = lerp(t1, t2, uvwCoord.x);

	float3 n1 = lerp(patch[0].normal, patch[1].normal, uvwCoord.y);
	float3 n2 = lerp(patch[2].normal, patch[3].normal, uvwCoord.y);
	float3 normPosition = lerp(n1, n2, uvwCoord.x);

	float3 tan1 = lerp(patch[0].tangent, patch[1].tangent, uvwCoord.y);
	float3 tan2 = lerp(patch[2].tangent, patch[3].tangent, uvwCoord.y);
	float3 tangentPosition = lerp(tan1, tan2, uvwCoord.x);

	float3 v1 = lerp(patch[0].position, patch[1].position, uvwCoord.y);
	float3 v2 = lerp(patch[3].position, patch[2].position, uvwCoord.y);
	vertexPosition = lerp(v1, v2, uvwCoord.x);

	float4 offset = displacementTex.SampleLevel(heightSampler0, texPosition, 0);
	//vertexPosition.z -= offset.x * 0.05f;




    // Determine the position of the new vertex.
	// Invert the y and Z components of uvwCoord as these coords are generated in UV space and therefore y is positive downward.
	// Alternatively you can set the output topology of the hull shader to cw instead of ccw (or vice versa).
	//vertexPosition = uvwCoord.x * patch[0].position + -uvwCoord.y * patch[1].position + -uvwCoord.z * patch[2].position;
		    
    // Calculate the position of the new vertex against the world, view, and projection matrices.
    output.position = mul(float4(vertexPosition, 1.0f), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Send the input color into the pixel shader.
    //output.colour = patch[0].colour;
	output.tex = texPosition;

	output.normal = mul(float4(normPosition, 1.f), worldMatrix);
	output.normal = mul(output.normal, viewMatrix);
	output.normal = mul(output.normal, projectionMatrix);

	output.tangent = mul(float4(tangentPosition, 1.f), worldMatrix);
	output.tangent = mul(output.tangent, viewMatrix);
	output.tangent = mul(output.tangent, projectionMatrix);

    return output;





}

