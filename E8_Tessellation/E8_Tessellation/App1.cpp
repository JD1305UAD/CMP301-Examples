// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{

}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	// Create Mesh object and shader object
	mesh = new QuadTess(renderer->getDevice(), renderer->getDeviceContext());
	shader = new TessellationShader(renderer->getDevice(), hwnd);

	tessellationFactor0 = 4;
	tessellationFactor1 = 4;
	tessellationFactor2 = 4;
	tessellationFactor3 = 4;
	tessellationFactorInside0 = 4;
	tessellationFactorInside1 = 4;
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.

}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool App1::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();

	// Send geometry data, set shader parameters, render object with shader
	mesh->sendData(renderer->getDeviceContext(), D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	shader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, tessellationFactor0, tessellationFactor1, tessellationFactor2, tessellationFactor3, tessellationFactorInside0, tessellationFactorInside1);
	shader->render(renderer->getDeviceContext(), mesh->getIndexCount());

	// Render GUI
	gui();

	// Swap the buffers
	renderer->endScene();

	return true;
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);
	ImGui::SliderInt("Tesselation factor 0", &tessellationFactor0, 1, 64);
	ImGui::SliderInt("Tesselation factor 1", &tessellationFactor1, 1, 64);
	ImGui::SliderInt("Tesselation factor 2", &tessellationFactor2, 1, 64);
	ImGui::SliderInt("Tesselation factor 3", &tessellationFactor3, 1, 64);
	ImGui::SliderInt("Tesselation factor Inside 0", &tessellationFactorInside0, 1, 64);
	ImGui::SliderInt("Tesselation factor Inside 1", &tessellationFactorInside1, 1, 64);

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

