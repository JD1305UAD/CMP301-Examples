// Light pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D dockTexture : register(t0);
Texture2D depthMapTexture : register(t1);

SamplerState sampler0 : register(s0);
SamplerState shadowSampler : register(s1);

cbuffer LightBuffer : register(b0)
{
	float4 ambientColour;
	float4 diffuseColour;
	float4 specularColour;
	float3 lightDirection;
	float specularPower;
	int shaderType;
	float3 padding;
};

cbuffer ShadowBuffer : register(b1)
{
	float shadowMapBias;
	float3 paddingShadow;
};


struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewVector : TEXCOORD1;
	float4 depthPosition : TEXCOORD2;
	float4 lightViewPos : TEXCOORD3;
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
	float4 lightColour = float4(0.f, 0.f, 0.f, 1.f);
	float4 specular;
	float lightDepthValue;

	//Depth shaders
	if (shaderType == 1)
	{
		float depthValue;
		// Get the depth value of the pixel by dividing the Z pixel depth by the homogeneous W coordinate.
		depthValue = input.depthPosition.z / input.depthPosition.w;
		return float4(depthValue, depthValue, depthValue, 1.0f);
	}

	// Calculate the projected texture coordinates.
	float2 pTexCoord = input.lightViewPos.xy / input.lightViewPos.w;
	pTexCoord *= float2(0.5, -0.5);
	pTexCoord += float2(0.5f, 0.5f);

	// Determine if the projected coordinates are in the 0 to 1 range.  If not don't do lighting.
	if (pTexCoord.x < 0.f || pTexCoord.x > 1.f || pTexCoord.y < 0.f || pTexCoord.y > 1.f)
	{
		return textureColour;
	}

	// Sample the shadow map (get depth of geometry)
	float depthValue;
	depthValue = depthMapTexture.Sample(shadowSampler, pTexCoord).r;
	// Calculate the depth from the light.
	lightDepthValue = input.lightViewPos.z / input.lightViewPos.w;
	lightDepthValue -= shadowMapBias;

	// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
	if (lightDepthValue < depthValue)
	{
		lightColour = calculateLighting(-lightDirection, input.normal, diffuseColour);
	}


	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
	textureColour = dockTexture.Sample(sampler0, input.tex);

	lightColour = saturate(lightColour + ambientColour);
	return saturate(lightColour) * textureColour;
}