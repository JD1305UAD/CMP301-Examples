// Quad Mesh
// Simple square mesh, with texture coordinates and normals.

#ifndef _QUADMESH_H_
#define _QUADMESH_H_

#include "BaseMesh.h"

using namespace DirectX;

class QuadMesh : public BaseMesh
{

public:
	QuadMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~QuadMesh();

	//void sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top);

protected:
	void initBuffers(ID3D11Device* device);
	
};

#endif