// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
	mesh = nullptr;
	shader = nullptr;
	testSphereMesh = nullptr;
	testSphere = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	textureMgr->loadTexture(L"DefaultDiffuse", L"res/water.png");

	// Create Mesh object and shader object
	mesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	shader = new ManipulationShader(renderer->getDevice(), hwnd);

	testSphereMesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());
	testSphere = new TestSphere(renderer->getDevice(), hwnd);

	light = new Light;
	light->setAmbientColour(0.8f, 0.8f, 0.8f, 1.0f);
	light->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	light->setDirection(0.7f, -0.7f, 0.0f);
	light->setSpecularColour(1.f, 1.f, 1.f, 1.f);
	light->setSpecularPower(10.f);

	

	steepness1 = 0.15f;
	steepness2 = 0.15f;
	steepness3 = 0.15f;

	frequency = 0.7f;
	speed = 0.5f;

	wavelength1 = 60.f;
	wavelength2= 31.f;
	wavelength3 = 18.f;

	


}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	if (mesh)
	{
		delete mesh;
		mesh = 0;
	}

	if (shader)
	{
		delete shader;
		shader = 0;
	}

	if (testSphere)
	{
		delete testSphere;
		testSphere = 0;
	}

	if (testSphereMesh)
	{
		delete testSphereMesh;
		testSphereMesh = 0;
	}
}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	timeTracked += timer->getTime();
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


	wave1 = XMFLOAT4(1, 0, steepness1, wavelength1);
	wave2 = XMFLOAT4(0, 1, steepness2, wavelength2);
	wave3 = XMFLOAT4(1, 1, steepness3, wavelength3);

	mesh->sendData(renderer->getDeviceContext());
	shader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"DefaultDiffuse"), light, timeTracked, wave1, wave2, wave3, speed);
	shader->render(renderer->getDeviceContext(), mesh->getIndexCount());



	//XMMATRIX testSphereMatrix = worldMatrix;
	//testSphereMatrix *= XMMatrixTranslation(0.f, 5.f, 0.f);

	//testSphereMesh->sendData(renderer->getDeviceContext());
	//testSphere->setShaderParameters(renderer->getDeviceContext(), testSphereMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"DefaultDiffuse"), light);
	//testSphere->render(renderer->getDeviceContext(), testSphereMesh->getIndexCount());


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
	ImGui::SliderFloat("Wavelength1", &wavelength1, 0.1f, 50);
	ImGui::SliderFloat("Wavelength2", &wavelength2, 0.1f, 50);
	ImGui::SliderFloat("Wavelength3", &wavelength3, 0.1f, 50);
	ImGui::SliderFloat("Steepness1", &steepness1, 0.1f, 50);
	ImGui::SliderFloat("Steepness2", &steepness2, 0.1f, 50);
	ImGui::SliderFloat("Steepness3", &steepness3, 0.1f, 50);

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

