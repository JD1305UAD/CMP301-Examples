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
	cubeMesh = new CubeTess(renderer->getDevice(), renderer->getDeviceContext());
	shader = new TessellationShader(renderer->getDevice(), hwnd);

	testSphereMesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());
	testSphere = new TestSphere(renderer->getDevice(), hwnd);

	textureMgr->loadTexture(L"woodTex", L"res/WoodColour.jpg");
	textureMgr->loadTexture(L"woodDis", L"res/WoodDis.png");
	textureMgr->loadTexture(L"woodNorm", L"res/WoodNorm.jpg");

	tessellationFactor0 = 64;
	tessellationFactor1 = 4;
	tessellationFactor2 = 4;
	tessellationFactor3 = 4;
	tessellationFactorInside0 = 4;
	tessellationFactorInside1 = 4;

	lightPosX = 5.f;
	lightPosY = 0.f;
	lightPosZ = -5.f;

	//Create light
	light = new Light;
	light->setAmbientColour(0.2f, 0.2f, 0.2f, 1.0f);
	light->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	light->setDirection(0.f, -0.9f, 1.0f);
	light->setPosition(5.f, 0.f, -5.f);
	light->setSpecularColour(1.f, 1.f, 1.f, 1.f);
	light->setSpecularPower(15.f);
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

	light->setPosition(lightPosX, lightPosY, lightPosZ);


	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();


	XMMATRIX testMatrix = worldMatrix;
	testMatrix = XMMatrixTranslation(lightPosX, lightPosY, lightPosZ);
	testSphereMesh->sendData(renderer->getDeviceContext());
	testSphere->setShaderParameters(renderer->getDeviceContext(), testMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"woodTex"), light, camera->getPosition());
	testSphere->render(renderer->getDeviceContext(), testSphereMesh->getIndexCount());

	// Send geometry data, set shader parameters, render object with shader
	cubeMesh->sendData(renderer->getDeviceContext(), D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	shader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, tessellationFactor0, tessellationFactor1, tessellationFactor2, 
		tessellationFactor3, tessellationFactorInside0, tessellationFactorInside1, textureMgr->getTexture(L"woodTex"), textureMgr->getTexture(L"woodDis"), textureMgr->getTexture(L"woodNorm"), light, camera->getPosition());
	shader->render(renderer->getDeviceContext(), cubeMesh->getIndexCount());

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
	//ImGui::SliderInt("Tesselation factor 1", &tessellationFactor1, 1, 64);
	//ImGui::SliderInt("Tesselation factor 2", &tessellationFactor2, 1, 64);
	//ImGui::SliderInt("Tesselation factor 3", &tessellationFactor3, 1, 64);
	//ImGui::SliderInt("Tesselation factor Inside 0", &tessellationFactorInside0, 1, 64);
	//ImGui::SliderInt("Tesselation factor Inside 1", &tessellationFactorInside1, 1, 64);
	ImGui::SliderFloat("Light X", &lightPosX, -10.f, 10.f);
	ImGui::SliderFloat("Light Y", &lightPosY, -10.f, 10.f);
	ImGui::SliderFloat("Light Z", &lightPosZ, -10.f, 10.f);

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

