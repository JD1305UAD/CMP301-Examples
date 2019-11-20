#pragma once
#include "DXF.h"

using namespace std;
using namespace DirectX;

class TestSphere : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT3 direction;
		float specularPower;
		XMFLOAT3 cameraPos;
		float paddingL;
	};

	/*struct IndexBufferType
	{
		float vertexNo;
		XMFLOAT3 padding;
	};*/

public:
	TestSphere(ID3D11Device* device, HWND hwnd);
	~TestSphere();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* texture,
		Light* light, XMFLOAT3 cameraPos_);

private:
	void initShader(const wchar_t* cs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* lightBuffer;
	//ID3D11Buffer* matrixBuffer;
	//ID3D11Buffer* indexBuffer;

};