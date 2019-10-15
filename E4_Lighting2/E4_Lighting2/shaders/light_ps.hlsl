// Light pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

cbuffer LightBuffer : register(b0)
{
	float4 ambient;
	float4 diffuse;
	float3 position;
	float padding;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : TEXCOORD1;
};

// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateLighting(float3 lightDirection, float3 normal, float4 ldiffuse, float attenuation)
{
	float intensity = saturate(dot(normal, lightDirection));
	ldiffuse = ldiffuse * attenuation;
	float4 colour = saturate(ldiffuse * intensity);
	//colour = colour * attenuation;
	return colour;
}

float calculateAttenuation(float distance)
{
	float constantFactor = 0.5f;
	float linearFactor = 0.125f;
	float quadraticFactor = 0.0f;
	// 
	float4 attenuation = 1 / (constantFactor + (linearFactor * distance) + (quadraticFactor * pow(distance, 2)));

	return attenuation;
}

float4 main(InputType input) : SV_TARGET
{
	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
	float4 textureColour = texture0.Sample(sampler0, input.tex);
	float attenuation = calculateAttenuation(position - input.worldPosition);
	float3 lightVector = normalize(position - input.worldPosition);
	float4 lightColour = ambient + calculateLighting(lightVector, input.normal, diffuse, attenuation);
	
	return lightColour * textureColour;
}



