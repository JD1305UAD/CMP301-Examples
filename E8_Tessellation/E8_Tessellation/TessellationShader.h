// Light shader.h
// Basic single light shader setup
#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;


class TessellationShader : public BaseShader
{

private:
	struct TessellationBufferType
	{
		int tessellationFactor0;
		int tessellationFactor1;
		int tessellationFactor2;
		int tessellationFactor3;
		int tessellationFactorInside0;
		int tessellationFactorInside1;
		XMFLOAT2 padding;
	};

public:

	TessellationShader(ID3D11Device* device, HWND hwnd);
	~TessellationShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, int tessFactor0, int tessFactor1, int tessFactor2, int tessFactor3, int tessFactorInside0, int tessFactorInside1, ID3D11ShaderResourceView* textureColour, ID3D11ShaderResourceView* textureDis);

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* tessellationBuffer;

	ID3D11SamplerState* sampleStateColour;
	ID3D11SamplerState* sampleStateDis;
};
