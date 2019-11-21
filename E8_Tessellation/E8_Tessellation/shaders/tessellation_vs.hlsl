// Tessellation vertex shader.
// Doesn't do much, could manipulate the control points
// Pass forward data, strip out some values not required for example.


struct InputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct OutputType
{
    float3 position : POSITION;
	float2 tex : TEXCOORD0;
};

OutputType main(InputType input)
{
    OutputType output;


	 // Pass the vertex position into the hull shader.
    output.position = input.position;
    
	
    // Pass the input color into the hull shader.
  //  output.colour = float4(1.0, 0.0, 0.0, 1.0);
	output.tex = float2((input.tex.x * -2), (input.tex.y * -15));



    return output;
}
