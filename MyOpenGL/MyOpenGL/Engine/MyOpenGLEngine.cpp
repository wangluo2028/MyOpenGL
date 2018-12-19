#include "stdafx.h"
#include "MyOpenGLEngine.h"

int FMyOpenGLEngine::windowWidth = 800;
int FMyOpenGLEngine::windowHeight = 600;
FMyOpenGLEngine FMyOpenGLEngine::MyEngine;

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

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
