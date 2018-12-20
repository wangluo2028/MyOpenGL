#pragma once


#include "MyWorld.h"

class FMyOpenGLEngine
{
public:
	FMyOpenGLEngine();

	~FMyOpenGLEngine();

	static FMyOpenGLEngine* GetInstance();

	void glfwInitialSetup();

	bool glfwCreateWindowContext();

	bool gladInitialization();

	void RenderLoop();

	UMyWorld* GetWorld();

protected:
	void Terminate();

	static void FrameSizeCallBack(GLFWwindow *window, int width, int height);

	void ProcessInput(GLFWwindow *window);

protected:
	class GLFWwindow *window;

	static int windowWidth;
	static int windowHeight;

	UMyWorld *MyWorld;

	static FMyOpenGLEngine MyEngine;
};

