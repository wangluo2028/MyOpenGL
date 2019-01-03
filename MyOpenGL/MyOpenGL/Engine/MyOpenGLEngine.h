#pragma once

#include "Camera.h"
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

	static void ProcessInput(GLFWwindow *window);

	static void MouseMoveCallBack(GLFWwindow *window, double XOffset, double YOffset);

	static void MouseScrollCallBack(GLFWwindow *window, double XOffset, double YOffset);

public:
	struct GLFWwindow *window;

	static int windowWidth;
	static int windowHeight;
	static float LastFrame;
	static float DeltaTime;
	static bool bFirstMouse;
	static FVector2D LastMousePos;

	UMyWorld *MyWorld;

	static FMyOpenGLEngine MyEngine;

	static UCamera MyCamera;
};

