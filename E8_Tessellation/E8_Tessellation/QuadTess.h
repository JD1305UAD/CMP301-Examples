#pragma once
#include "BaseMesh.h"
using namespace DirectX;

class QuadTess : public BaseMesh
{

public:
	QuadTess(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~QuadTess();

	void sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top);

protected:
	void initBuffers(ID3D11Device* device);

};

