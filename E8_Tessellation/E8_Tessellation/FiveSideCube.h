#pragma once

#include "BaseMesh.h"

using namespace DirectX;

class FiveSideCube : public BaseMesh
{
public:
	FiveSideCube(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution = 20);
	~FiveSideCube();

protected:
	void initBuffers(ID3D11Device* device);
	int resolution;
};

