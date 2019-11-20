#include "BaseMesh.h"

using namespace DirectX;

class CubeTess : public BaseMesh
{

public:
	/** \brief Initialises and builds a cube mesh
	*
	* Can specify resolution of cube, this deteremines how many subdivisions are on each side of the cube.
	* @param device is the renderer device
	* @param device context is the renderer device context
	* @param resolution is a int for subdivision of the cube. Default is 20.
	*/
	CubeTess(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution = 20);
	~CubeTess();


	void sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top);
protected:
	void initBuffers(ID3D11Device* device);
	int resolution;
};