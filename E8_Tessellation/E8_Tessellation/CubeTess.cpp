#include "CubeTess.h"
// Cube Mesh
// Generates cube mesh at set resolution. Default res is 20.
// Mesh has texture coordinates and normals.
#include "cubemesh.h"

// Initialise vertex data, buffers and load texture.
CubeTess::CubeTess(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int lresolution)
{
	resolution = lresolution;
	initBuffers(device);
}


CubeTess::~CubeTess()
{
	// Run parent deconstructor
	BaseMesh::~BaseMesh();
}


void CubeTess::sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case control patch for tessellation.
	deviceContext->IASetPrimitiveTopology(top);
}

// Initialise geometry buffers (vertex and index).
// Generate and store cube vertices, normals and texture coordinates
void CubeTess::initBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	// 4 vertices per quad, res*res is face, times 6 for each face
	vertexCount = ((4 * resolution) * resolution) * 6;

	indexCount = vertexCount;

	// Create the vertex and index array.
	vertices = new VertexType[vertexCount];
	indices = new unsigned long[indexCount];


	//front face

			// Load the vertex array with data.
			vertices[0].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);  // Top left
			vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertices[1].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);  // Bottom left.
			vertices[1].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertices[2].position = XMFLOAT3(1.0f, -1.0f, -1.0f);  // Bottom right.
			vertices[2].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			vertices[3].position = XMFLOAT3(1.0f, 1.0f, -1.0f);  // Top right.
			vertices[3].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[3].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			// Load the index array with data.
			indices[0] = 0;  // Bottom left.
			indices[1] = 1;  // Top right.
			indices[2] = 2;  // Top left.
			indices[3] = 3;	// bottom right


	//back face

			// Load the vertex array with data.
			vertices[0].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);  // Top left
			vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[0].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			vertices[1].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);  // Bottom left.
			vertices[1].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[1].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			vertices[2].position = XMFLOAT3(1.0f, -1.0f, 1.0f);  // Bottom right.
			vertices[2].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[2].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			vertices[3].position = XMFLOAT3(1.0f, 1.0f, 1.0f);  // Top right.
			vertices[3].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[3].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			// Load the index array with data.
			indices[4] = 0;  // Bottom left.
			indices[5] = 1;  // Top right.
			indices[6] = 2;  // Top left.
			indices[7] = 3;	// bottom right

	//right face

			// Load the vertex array with data.
			vertices[0].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top left
			vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[0].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

			vertices[1].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom left.
			vertices[1].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[1].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

			vertices[2].position = XMFLOAT3(1.0f, -1.0f, 1.0f);  // Bottom right.
			vertices[2].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[2].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

			vertices[3].position = XMFLOAT3(1.0f, 1.0f, 1.0f);  // Top right.
			vertices[3].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[3].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);


			// Load the index array with data.
			indices[8] = 0;  // Bottom left.
			indices[9] = 1;  // Top right.
			indices[10] = 2;  // Top left.
			indices[11] = 3;	// bottom right
			

		

	//left face
	
			// Load the vertex array with data.
			
				// Load the vertex array with data.
			vertices[0].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);  // Top left
			vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[0].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

			vertices[1].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);  // Bottom left.
			vertices[1].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[1].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

			vertices[2].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);  // Bottom right.
			vertices[2].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[2].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

			vertices[3].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);  // Top right.
			vertices[3].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[3].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);



			// Load the index array with data.
			indices[12] = 0;  // Bottom left.
			indices[13] = 1;  // Top right.
			indices[14] = 2;  // Top left.
			indices[15] = 3;	// bottom right
			

	//top face
	
			// Load the vertex array with data.
			// Load the vertex array with data.
			vertices[0].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);  // Top left
			vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[0].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

			vertices[1].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);  // Bottom left.
			vertices[1].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[1].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

			vertices[2].position = XMFLOAT3(1.0f, 1.0f, -1.0f);  // Bottom right.
			vertices[2].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[2].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

			vertices[3].position = XMFLOAT3(1.0f, 1.0f, 1.0f);  // Top right.
			vertices[3].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[3].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);



			// Load the index array with data.
			indices[16] = 0;  // Bottom left.
			indices[17] = 1;  // Top right.
			indices[18] = 2;  // Top left.
			indices[19] = 3;	// bottom right

	//bottom face

			// Load the vertex array with data.
			vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);  // Top left
			vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[0].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

			vertices[1].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);  // Bottom left.
			vertices[1].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[1].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

			vertices[2].position = XMFLOAT3(1.0f, -1.0f, -1.0f);  // Bottom right.
			vertices[2].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[2].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

			vertices[3].position = XMFLOAT3(1.0f, -1.0f, 1.0f);  // Top right.
			vertices[3].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[3].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);



			// Load the index array with data.
			indices[20] = 0;  // Bottom left.
			indices[21] = 1;  // Top right.
			indices[22] = 2;  // Top left.
			indices[23] = 3;	// bottom right


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

