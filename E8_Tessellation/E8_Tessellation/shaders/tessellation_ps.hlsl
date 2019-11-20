// Tessellation pixel shader
// Output colour passed to stage.

Texture2D dockTexture : register(t0);
Texture2D normTex : register(t1);

SamplerState sampler0 : register(s0);
SamplerState normSampler : register(s1);

struct InputType
{
    float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
};


cbuffer LightBuffer : register(b0)
{
	float4 ambientColour;
	float4 diffuseColour;
	float4 specularColour;
	float3 lightDirection;
	float specularPower;
	float3 viewVector;
	float padding;
};





// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateLighting(float3 lightDirection, float3 normal, float4 diffuse)
{
	float intensity = saturate(dot(normal, lightDirection));
	float4 colour = saturate(diffuse * intensity);
	return colour;
}

/////////////////////Check view vector////////////////////////
float4 calcSpecular(float3 lightDirection, float3 normal, float3 viewVector, float4 specularColour, float4 specularPower)
{
	// blinn-phong specular calculation
	float3 halfway = normalize(lightDirection + viewVector);
	float specularIntensity = pow(max(dot(normal, halfway), 0.0), specularPower);
	return saturate(specularColour * specularIntensity);
}

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float4 specular;
	float4 lightColour;
	
	float3 normal = input.normal;

	//Load normal from normal map
	float4 normalMap = normTex.Sample(normSampler, input.tex);

	//Change normal map range from [0, 1] to [-1, 1]
	normalMap = (2.0f * normalMap) - 1.0f;

	//Make sure tangent is completely orthogonal to normal
	input.tangent = normalize(input.tangent - dot(input.tangent, normal) * normal);

	//Create the binormal
	float3 binormal = cross(normal, input.tangent);

	//Create the "Texture Space"
	float3x3 texSpace = float3x3(input.tangent, binormal, normal);

	//Convert normal from normal map to texture space and store in input.normal
	normal = normalize(mul(normalMap, texSpace));
	
	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
	textureColour = dockTexture.Sample(sampler0, input.tex);
	lightColour = ambientColour;
	lightColour += calculateLighting(-lightDirection, normal, diffuseColour);

	specular = calcSpecular(-lightDirection, normal, viewVector, specularColour, specularPower);


	float4 output = (lightColour * textureColour) + specular;
	return output * 5;
}