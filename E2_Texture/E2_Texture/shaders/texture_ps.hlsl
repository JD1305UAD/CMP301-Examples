// Texture pixel/fragment shader
// Basic fragment shader for rendering textured geometry

// Texture and sampler registers
Texture2D texture0 : register(t0);
Texture2D texture1 : register(t1);
SamplerState Sampler0 : register(s0);
//SamplerState Sampler1 : register(s1);


struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};


float4 main(InputType input) : SV_TARGET
{
	float4 textureColor;
float4 textureColor1;


	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = texture0.Sample(Sampler0, input.tex);
	textureColor1 = texture1.Sample(Sampler0, input.tex);

	//InvertColor
	//float4 inverseColor = float4(1.0f - textureColor.r, 1.0f - textureColor.g, 1.0f - textureColor.b, 1.0f);
	//return inverseColor;
	return lerp(textureColor, textureColor1, 0.5);

}