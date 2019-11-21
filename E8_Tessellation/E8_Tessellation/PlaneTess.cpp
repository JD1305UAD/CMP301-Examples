#include "PlaneTess.h"
// plane mesh
// Quad mesh made of many quads. Default is 100x100


// Initialise buffer and load texture.
PlaneTess::PlaneTess(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int lresolution)
{
	resolution = lresolution;
	initBuffers(device);
}

// Release resources.
PlaneTess::~PlaneTess()
{
	// Run parent deconstructor
	BaseMesh::~BaseMesh();
}

// Generate plane (including texture coordinates and normals).
void PlaneTess::initBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	int index, i, j, resolutionX, resolutionY;
	float positionX, positionZ, u, v, incrementX, incrementY;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	resolutionX = 10;
	resolutionY = 15;

	// Calculate the number of vertices 
	vertexCount = (resolutionX - 1) * (resolutionY - 1) * 8;

	indexCount = vertexCount;
	vertices = new VertexType[vertexCount];
	indices = new unsigned long[indexCount];


	index = 0;
	// UV coords.
	u = 0;
	v = 0;
	incrementX = 1.0f / resolutionX;
	incrementY = 1.0f / resolutionY;

	for (j = 0; j < (resolutionY - 1); j++)
	{
		for (i = 0; i < (resolutionX - 1); i++)
		{
			// Far left.
			positionX = (float)i;
			positionZ = (float)(j + 1);

			vertices[index].position = XMFLOAT3(positionX, 0, positionZ);
			vertices[index].texture = XMFLOAT2(u, v + incrementY);
			vertices[index].normal = XMFLOAT3(0.0, 1.0, 0.0);
			indices[index] = index;
			index++;


			// Near left
			positionX = (float)(i);
			positionZ = (float)(j);

			vertices[index].position = XMFLOAT3(positionX, 0, positionZ);
			vertices[index].texture = XMFLOAT2(u, v);
			vertices[index].normal = XMFLOAT3(0.0, 1.0, 0.0);
			indices[index] = index;
			index++;


			// Near right
			positionX = (float)(i + 1);
			positionZ = (float)(j);

			vertices[index].position = XMFLOAT3(positionX, 0, positionZ);
			vertices[index].texture = XMFLOAT2(u + incrementX, v);
			vertices[index].normal = XMFLOAT3(0.0, 1.0, 0.0);
			indices[index] = index;
			index++;


			// Far right.
			positionX = (float)(i + 1);
			positionZ = (float)(j + 1);

			vertices[index].position = XMFLOAT3(positionX, 0, positionZ);
			vertices[index].texture = XMFLOAT2(u + incrementX, v + incrementY);
			vertices[index].normal = XMFLOAT3(0.0, 1.0, 0.0);
			indices[index] = index;
			index++;

			u += incrementX;
		}

		u = 0;
		v += incrementY;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	// Create the index buffer.
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
}

// Override sendData() to change topology type. Control point patch list is required for tessellation.
void PlaneTess::sendData(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case control patch for tessellation.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
}



