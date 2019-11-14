#pragma once
#include "DXF.h"

using namespace std;
using namespace DirectX;

class DockShader : public BaseShader
{
private:

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT3 direction;
		float specularPower;
		int shaderType;
		XMFLOAT3 padding;
	};

	struct ShadowBufferType
	{
		float shadowMapBias;
		XMFLOAT3 padding;
	};
public:
	DockShader(ID3D11Device* device, HWND hwnd);
	~DockShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* textureColour, ID3D11ShaderResourceView* textureDis, ID3D11ShaderResourceView* shadowTexture, ID3D11ShaderResourceView* depthMap, float bias, Light* light, int shaderType);

private:
	void initShader(const wchar_t* cs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleStateColour;
	ID3D11SamplerState* sampleStateDis;
	ID3D11SamplerState* sampleStateShadow;
	//ID3D11SamplerState* sampleBackState;
	//ID3D11SamplerState* sampleRightState;
	//ID3D11SamplerState* sampleLeftState;
	//ID3D11SamplerState* sampleTopState;
	//ID3D11SamplerState* sampleBottomState;
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* shadowBuffer;
};