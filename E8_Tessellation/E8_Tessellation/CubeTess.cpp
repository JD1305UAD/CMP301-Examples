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
			indices[0] = 0;  // Top left
			indices[1] = 1;  // Bottom left
			indices[2] = 2;  // Bottom right.
			indices[3] = 3;	// bottom right


	//back face

			// Load the vertex array with data.
			vertices[4].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);  // Top left
			vertices[4].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[4].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			vertices[5].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);  // Bottom left.
			vertices[5].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[5].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			vertices[6].position = XMFLOAT3(1.0f, -1.0f, 1.0f);  // Bottom right.
			vertices[6].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[6].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			vertices[7].position = XMFLOAT3(1.0f, 1.0f, 1.0f);  // Top right.
			vertices[7].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[7].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

			// Load the index array with data.
			indices[4] = 4;  // Bottom left.
			indices[5] = 7;  // Top right.
			indices[6] = 6;  // Top left.
			indices[7] = 5;	// bottom right

	//right face

			// Load the vertex array with data.
			vertices[8].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top left
			vertices[8].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[8].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

			vertices[9].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom left.
			vertices[9].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[9].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

			vertices[10].position = XMFLOAT3(1.0f, -1.0f, 1.0f);  // Bottom right.
			vertices[10].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[10].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

			vertices[11].position = XMFLOAT3(1.0f, 1.0f, 1.0f);  // Top right.
			vertices[11].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[11].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);


			// Load the index array with data.
			indices[8] = 8;  // Bottom left.
			indices[9] = 9;  // Top right.
			indices[10] = 10;  // Top left.
			indices[11] = 11;	// bottom right
			

		

	//left face
	
			// Load the vertex array with data.
			
				// Load the vertex array with data.
			vertices[12].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);  // Top left
			vertices[12].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[12].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

			vertices[13].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);  // Bottom left.
			vertices[13].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[13].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

			vertices[14].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);  // Bottom right.
			vertices[14].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[14].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

			vertices[15].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);  // Top right.
			vertices[15].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[15].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);



			// Load the index array with data.
			indices[12] = 12;  // Bottom left.
			indices[13] = 13;  // Top right.
			indices[14] = 14;  // Top left.
			indices[15] = 15;	// bottom right
			

	//top face
	
			// Load the vertex array with data.
			// Load the vertex array with data.
			vertices[16].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);  // Top left
			vertices[16].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[16].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

			vertices[17].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);  // Bottom left.
			vertices[17].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[17].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
					  
			vertices[18].position = XMFLOAT3(1.0f, 1.0f, -1.0f);  // Bottom right.
			vertices[18].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[18].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

			vertices[19].position = XMFLOAT3(1.0f, 1.0f, 1.0f);  // Top right.
			vertices[19].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[19].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);



			// Load the index array with data.
			indices[16] = 16;  // Bottom left.
			indices[17] = 17;  // Top right.
			indices[18] = 18;  // Top left.
			indices[19] = 19;	// bottom right

	//bottom face

			// Load the vertex array with data.
			vertices[20].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);  // Top left
			vertices[20].texture = XMFLOAT2(0.0f, 1.0f);
			vertices[20].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

			vertices[21].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);  // Bottom left.
			vertices[21].texture = XMFLOAT2(0.0f, 0.0f);
			vertices[21].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

			vertices[22].position = XMFLOAT3(1.0f, -1.0f, -1.0f);  // Bottom right.
			vertices[22].texture = XMFLOAT2(1.0f, 1.0f);
			vertices[22].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

			vertices[23].position = XMFLOAT3(1.0f, -1.0f, 1.0f);  // Top right.
			vertices[23].texture = XMFLOAT2(1.0f, 0.0f);
			vertices[23].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);



			// Load the index array with data.
			indices[20] = 20;  // Bottom left.
			indices[21] = 21;  // Top right.
			indices[22] = 22;  // Top left.
			indices[23] = 23;	// bottom right


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

