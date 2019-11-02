// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "ManipulationShader.h"
#include "TestSphere.h"

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
	ManipulationShader* shader;
	PlaneMesh* mesh;
	Light* light;
	SphereMesh* testSphereMesh;
	TestSphere* testSphere;


	float timeTracked;
	float steepness1;
	float steepness2;
	float steepness3;
	float frequency;
	float speed;
	float wavelength1;
	float wavelength2;
	float wavelength3;
	XMFLOAT4 wave1;
	XMFLOAT4 wave2;
	XMFLOAT4 wave3;
};

#endif