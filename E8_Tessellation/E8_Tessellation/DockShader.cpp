#include "DockShader.h"

DockShader::DockShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"dock_vs.cso", L"dock_ps.cso");
}


DockShader::~DockShader()
{
	// Release the sampler states.
	if (sampleStateColour)
	{
		sampleStateColour->Release();
		sampleStateColour = 0;
	}

	if (sampleStateDis)
	{
		sampleStateDis->Release();
		sampleStateDis = 0;
	}

	//if (sampleBackState)
	//{
	//	sampleBackState->Release();
	//	sampleBackState = 0;
	//}

	//if (sampleRightState)
	//{
	//	sampleRightState->Release();
	//	sampleRightState = 0;
	//}

	//if (sampleLeftState)
	//{
	//	sampleLeftState->Release();
	//	sampleLeftState = 0;
	//}

	//if (sampleTopState)
	//{
	//	sampleTopState->Release();
	//	sampleTopState = 0;
	//}

	//if (sampleBottomState)
	//{
	//	sampleBottomState->Release();
	//	sampleBottomState = 0;
	//}


	// Release the matrix constant buffer.
	if (matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}

	// Release the layout.
	if (layout)
	{
		layout->Release();
		layout = 0;
	}

	// Release the light constant buffer.
	if (lightBuffer)
	{
		lightBuffer->Release();
		lightBuffer = 0;
	}

	if (shadowBuffer)
	{
		shadowBuffer->Release();
		shadowBuffer = 0;
	}

	//Release base shader components
	BaseShader::~BaseShader();
}

void DockShader::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC lightBufferDesc;
	D3D11_BUFFER_DESC shadowBufferDesc;

	// Load (+ compile) shader files
	loadVertexShader(vsFilename);
	loadPixelShader(psFilename);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);

	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	renderer->CreateSamplerState(&samplerDesc, &sampleStateColour);
	renderer->CreateSamplerState(&samplerDesc, &sampleStateDis);
	//renderer->CreateSamplerState(&samplerDesc, &sampleBackState);
	//renderer->CreateSamplerState(&samplerDesc, &sampleRightState);
	//renderer->CreateSamplerState(&samplerDesc, &sampleLeftState);
	//renderer->CreateSamplerState(&samplerDesc, &sampleTopState);
	//renderer->CreateSamplerState(&samplerDesc, &sampleBottomState);

	// Sampler for shadow map sampling.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.BorderColor[0] = 1.0f;
	samplerDesc.BorderColor[1] = 1.0f;
	samplerDesc.BorderColor[2] = 1.0f;
	samplerDesc.BorderColor[3] = 1.0f;
	renderer->CreateSamplerState(&samplerDesc, &sampleStateShadow);

	// Setup light buffer
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;
	renderer->CreateBuffer(&lightBufferDesc, NULL, &lightBuffer);

	shadowBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	shadowBufferDesc.ByteWidth = sizeof(LightBufferType);
	shadowBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	shadowBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	shadowBufferDesc.MiscFlags = 0;
	shadowBufferDesc.StructureByteStride = 0;
	renderer->CreateBuffer(&shadowBufferDesc, NULL, &shadowBuffer);
}


void DockShader::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* textureColour, ID3D11ShaderResourceView* textureDis, ID3D11ShaderResourceView* shadowTexture, ID3D11ShaderResourceView* depthMap, float bias, Light* light, int shaderT)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	ShadowBufferType* shadowPtr;

	XMMATRIX tworld, tview, tproj;


	// Transpose the matrices to prepare them for the shader.

	tworld = XMMatrixTranspose(worldMatrix);
	tview = XMMatrixTranspose(viewMatrix);
	tproj = XMMatrixTranspose(projectionMatrix);
	XMMATRIX tLightViewMatrix = XMMatrixTranspose(light->getViewMatrix());
	XMMATRIX tLightProjectionMatrix = XMMatrixTranspose(light->getOrthoMatrix());
	result = deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = tworld;// worldMatrix;
	dataPtr->view = tview;
	dataPtr->projection = tproj;
	dataPtr->lightView = tLightViewMatrix;
	dataPtr->lightProjection = tLightProjectionMatrix;
	deviceContext->Unmap(matrixBuffer, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &matrixBuffer);

	////Additional
	//// Send light data to pixel shader
	LightBufferType* lightPtr;
	deviceContext->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	lightPtr = (LightBufferType*)mappedResource.pData;
	lightPtr->ambient = light->getAmbientColour();
	lightPtr->diffuse = light->getDiffuseColour();
	lightPtr->specular = light->getSpecularColour();
	lightPtr->direction = light->getDirection();
	lightPtr->specularPower = light->getSpecularPower();
	lightPtr->shaderType = shaderT;
	lightPtr->padding = XMFLOAT3(0.f, 0.f, 0.f);
	deviceContext->Unmap(lightBuffer, 0);
	deviceContext->PSSetConstantBuffers(0, 1, &lightBuffer);

	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &textureColour);
	deviceContext->VSSetShaderResources(0, 1, &textureDis);
	//deviceContext->PSSetShaderResources(1, 1, &textureBack);
	//deviceContext->PSSetShaderResources(2, 1, &textureRight);
	//deviceContext->PSSetShaderResources(3, 1, &textureLeft);
	//deviceContext->PSSetShaderResources(4, 1, &textureTop);
	//deviceContext->PSSetShaderResources(5, 1, &textureBottom);
	deviceContext->PSSetSamplers(0, 1, &sampleStateColour);
	deviceContext->VSSetSamplers(0, 1, &sampleStateDis);
	/*deviceContext->PSSetSamplers(1, 1, &sampleBackState);
	deviceContext->PSSetSamplers(2, 1, &sampleFrontState);
	deviceContext->PSSetSamplers(3, 1, &sampleBackState);
	deviceContext->PSSetSamplers(4, 1, &sampleFrontState);
	deviceContext->PSSetSamplers(5, 1, &sampleBackState);*/
}