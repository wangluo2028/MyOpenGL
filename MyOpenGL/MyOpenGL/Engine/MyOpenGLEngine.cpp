#include "stdafx.h"
#include "MyOpenGLEngine.h"

int FMyOpenGLEngine::windowWidth = 800;
int FMyOpenGLEngine::windowHeight = 600;
FMyOpenGLEngine FMyOpenGLEngine::MyEngine;
UCamera FMyOpenGLEngine::MyCamera;
float FMyOpenGLEngine::LastFrame = 0.0f;
float FMyOpenGLEngine::DeltaTime = 0.0f;
bool FMyOpenGLEngine::bFirstMouse = true;
FVector2D FMyOpenGLEngine::LastMousePos;

FMyOpenGLEngine::FMyOpenGLEngine()
{
	window = nullptr;

	MyWorld = new UMyWorld();
}

FMyOpenGLEngine::~FMyOpenGLEngine()
{
	delete MyWorld;

	Terminate();
}

FMyOpenGLEngine* FMyOpenGLEngine::GetInstance()
{
	return &MyEngine;
}

void FMyOpenGLEngine::glfwInitialSetup()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

bool FMyOpenGLEngine::glfwCreateWindowContext()
{
	window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", nullptr, nullptr);
	if (window == NULL)
	{
		return false;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, FMyOpenGLEngine::FrameSizeCallBack);
	glfwSetCursorPosCallback(window, FMyOpenGLEngine::MouseMoveCallBack);
	glfwSetScrollCallback(window, FMyOpenGLEngine::MouseScrollCallBack);

	return true;
}

bool FMyOpenGLEngine::gladInitialization()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	return true;
}

void FMyOpenGLEngine::RenderLoop()
{
	// wire frame mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		float CurrentFrame = glfwGetTime();
		DeltaTime = CurrentFrame - LastFrame;
		LastFrame = CurrentFrame;

		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (UMyObjectMesh *MyMesh : MyWorld->GetMeshesInWorld())
		{
			MyMesh->Render();
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

UMyWorld* FMyOpenGLEngine::GetWorld()
{
	return MyWorld;
}

void FMyOpenGLEngine::Terminate()
{
	glfwTerminate();
}

void FMyOpenGLEngine::FrameSizeCallBack(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void FMyOpenGLEngine::ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		MyCamera.ProcessKeyboardInput(EFront, DeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		MyCamera.ProcessKeyboardInput(EBack, DeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		MyCamera.ProcessKeyboardInput(ELeft, DeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		MyCamera.ProcessKeyboardInput(ERight, DeltaTime);
}

void FMyOpenGLEngine::MouseMoveCallBack(GLFWwindow *window, double XOffset, double YOffset)
{
	if (bFirstMouse)
	{
		LastMousePos = FVector2D(XOffset, YOffset);
		bFirstMouse = false;
	}

	float DeltaX = XOffset - LastMousePos.X;
	float DeltaY = YOffset - LastMousePos.Y;
	LastMousePos = FVector2D(XOffset, YOffset);

	MyCamera.ProcessMouseInput(DeltaX, DeltaY);
}

void FMyOpenGLEngine::MouseScrollCallBack(GLFWwindow *window, double XOffset, double YOffset)
{
	MyCamera.ProcessMouseScroll(YOffset);
}
