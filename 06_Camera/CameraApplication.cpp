#include "CameraApplication.h"
#include <SOIL/SOIL.h>

CameraApplication::CameraApplication(std::string name, int width, int height)
	: Application(name, width, height)
{
}

CameraApplication::~CameraApplication()
{
	if (mCameraDemo)
	{
		delete mCameraDemo;
	}
	if (mCamera)
	{
		delete mCamera;
	}
}

void CameraApplication::Initialize()
{
	mCamera = new FirstPersonCamera(*this);
	mComponents.push_back(mCamera);

	mCameraDemo = new CameraComponent(*this, *mCamera);
	mComponents.push_back(mCameraDemo);

	mBackgroundColor = { 0.2f, 0.3f, 0.3f, 1.0f };

	glEnable(GL_DEPTH_TEST);
	Application::Initialize();
}

void CameraApplication::Draw(float DeltaSeconds)
{
	glClearBufferfv(GL_COLOR, 0, &mBackgroundColor[0]);
	glClear(GL_DEPTH_BUFFER_BIT);

	Application::Draw(DeltaSeconds);

	glfwSwapBuffers(window);
}

