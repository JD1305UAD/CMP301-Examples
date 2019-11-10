// Tessellation pixel shader
// Output colour passed to stage.

Texture2D dockTexture : register(t0);
SamplerState sampler0 : register(s0);


struct InputType
{
    float4 position : SV_POSITION;
   // float4 colour : COLOR;
	float2 tex : TEXCOORD0;
};

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
	textureColour = dockTexture.Sample(sampler0, input.tex);

    return textureColour;
}