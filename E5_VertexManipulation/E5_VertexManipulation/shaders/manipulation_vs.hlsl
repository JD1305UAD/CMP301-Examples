// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader
cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer timeBuffer : register(b1)
{
	float timer;
	float steepness;
	float frequency;
	float speed;
};

cbuffer waveBuffer : register(b2)
{
	float4 wave1;
	float4 wave2;
	float4 wave3;
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

float3 GerstnerWave(
	float4 wave, float3 p, inout float3 tangent, inout float3 binormal
) {
	float steepness = wave.z;
	float wavelength = wave.w;
	float k = 2 * (3.141 / wavelength);
	float c = sqrt(9.8 / k);
	float2 d = normalize(wave.xy);
	float f = k * (dot(d, p.xz) - c * timer);
	float a = steepness / k;

	//p.x += d.x * (a * cos(f));
	//p.y = a * sin(f);
	//p.z += d.y * (a * cos(f));

	tangent += float3(
		-d.x * d.x * (steepness * sin(f)),
		d.x * (steepness * cos(f)),
		-d.x * d.y * (steepness * sin(f))
		);
	binormal += float3(
		-d.x * d.y * (steepness * sin(f)),
		d.y * (steepness * cos(f)),
		-d.y * d.y * (steepness * sin(f))
		);
	return float3(
		d.x * (a * cos(f)),
		a * sin(f),
		d.y * (a * cos(f))
		);
}

OutputType main(InputType input)
{
	OutputType output;

	//offset position based on sine wave
	//input.position.y= sin(input.position.x + timer);

	

	//float2 direction = float2(1, 1);

	//Phase speed of waves on Earth
	//float c = sqrt(float(9.8 / frequency));


	//float2 d = normalize(direction);
	//float f = frequency * (dot(d, input.position.xz) - (speed * timer));

	//float f = frequency * (input.position.x - (c * timer));

	//offset position based on sine wave
	//input.position.y += amplitude * sin((input.position.x * frequency) + (timer * speed));

	//input.position.x += amplitude * cos(f);
	//input.position.y = amplitude * sin(f);

	//float a = steepness / frequency;

	//input.position.x += d.x * (a * cos(f));
	//input.position.y = a * sin(f);
	//input.position.z += d.y * (a * cos(f));



	//tangent
	//float3 tangent = float3(1 - d.x * d.x * (steepness *sin(f)),
	//						d.x * (steepness * cos(f)),
	//						-d.x * d.y * (steepness * sin(f)));

	//float3 binormal = float3(-d.x * d.y * (steepness * sin(f)),
	//						d.y * (steepness * cos(f)),
	//						1 - d.y * d.y * (steepness * sin(f)));

	float3 vertPoint = input.position.xyz;
	float3 tangent = float3(1, 0, 0);
	float3 binormal = float3(0, 0, 1);
	float3 p = vertPoint;
	p += GerstnerWave(wave1, vertPoint, tangent, binormal);
	p += GerstnerWave(wave2, vertPoint, tangent, binormal);
	p += GerstnerWave(wave3, vertPoint, tangent, binormal);

	float3 norm = normalize(cross(binormal, tangent));
	input.position.xyz = p.xyz;
	input.normal = norm;

	//modify normals
	//float3 norm = float3(amplitude * frequency * cos((input.position.x * frequency) + (speed * timer)), 0, amplitude * frequency * cos((input.position.x * frequency) + (speed * timer)));
	//float3 norm = float3(-tangent.y, tangent.x, 0);


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