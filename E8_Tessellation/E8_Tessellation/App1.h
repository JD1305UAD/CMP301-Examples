// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "TessellationShader.h"
#include "QuadTess.h"
#include "TestSphere.h"
#include "CubeTess.h"
#include "PlaneTess.h"
#include "FiveSideCube.h"
#include "DockShader.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

private:
	//TessellationMesh* mesh;
	TessellationShader* shader;
	QuadTess* mesh;
	CubeTess* cubeMesh;
	SphereMesh* testSphereMesh;
	TestSphere* testSphere;
	PlaneTess* planeMesh;

	FiveSideCube* fiveSideMesh;
	TestSphere* dockShader;

	Light* light;

	float lightPosX;
	float lightPosY;
	float lightPosZ;

	int tessellationFactor0;
	int tessellationFactor1;
	int tessellationFactor2;
	int tessellationFactor3;
	int tessellationFactorInside0;
	int tessellationFactorInside1;


};

#endif