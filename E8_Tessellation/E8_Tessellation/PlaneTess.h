#pragma once
#include "BaseMesh.h"

class PlaneTess : public BaseMesh
{

public:
	/** \brief Initialises and builds a plane mesh
	*
	* Can specify resolution of plane, this deteremines how many subdivisions of the plane.
	* @param device is the renderer device
	* @param device context is the renderer device context
	* @param resolution is a int for subdivision of the plane. The number of unit quad on each axis. Default is 100.
	*/
	PlaneTess(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int resolution = 100);
	~PlaneTess();

	void sendData(ID3D11DeviceContext* deviceContext);

protected:
	void initBuffers(ID3D11Device* device);
	int resolution;
};
