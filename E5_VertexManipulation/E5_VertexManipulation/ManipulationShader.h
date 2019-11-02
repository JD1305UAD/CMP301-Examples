#pragma once

#include "DXF.h"
#include "timer.h"

using namespace std;
using namespace DirectX;

class ManipulationShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 specularColour;
		XMFLOAT3 direction;
		float specularPower;
	};

	struct TimeBufferType
	{ 
		float time;
		//float frequency;
		float speed;
		XMFLOAT2 padding;
		/*XMFLOAT3 padding; */
	};

	struct WaveBufferType
	{
		XMFLOAT4 wave1; //(direction X, Y, steepness, wavelength)
		XMFLOAT4 wave2; //(direction X, Y, steepness, wavelength)
		XMFLOAT4 wave3; //(direction X, Y, steepness, wavelength)
	};

public:
	ManipulationShader(ID3D11Device* device, HWND hwnd);
	~ManipulationShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, Light* light, float timer, XMFLOAT4 _wave1, XMFLOAT4 _wave2, XMFLOAT4 _wave3, float spe);

private:
	void initShader(const wchar_t* cs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* timeBuffer;
	ID3D11Buffer* waveBuffer;
};

