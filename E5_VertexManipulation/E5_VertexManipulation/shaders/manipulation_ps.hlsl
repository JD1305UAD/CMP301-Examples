// Light pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D waterTexture : register(t0);
SamplerState sampler0 : register(s0);


cbuffer LightBuffer : register(b0)
{
	float4 ambientColour;
	float4 diffuseColour;
	float4 specularColour;
	float3 lightDirection;
	float specularPower;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewVector : TEXCOORD1;
};



// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateLighting(float3 lightDirection, float3 normal, float4 diffuse)
{
	float intensity = saturate(dot(normal, lightDirection));
	float4 colour = saturate(diffuse * intensity);
	return colour;
}

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
	float4 lightColour;
	float4 specular;

	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
	textureColour = waterTexture.Sample(sampler0, input.tex);
	lightColour = ambientColour;
	lightColour += calculateLighting(-lightDirection, input.normal, diffuseColour);
	lightColour.a = 0.8f;

	specular = calcSpecular(-lightDirection, input.normal, input.viewVector, specularColour, specularPower);

	return (lightColour * textureColour) + specular;
}




