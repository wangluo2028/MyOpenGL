#include "stdafx.h"

#include "Engine/MyOpenGLEngine.h"

int main()
{
	FMyOpenGLEngine *MyEnginePtr = FMyOpenGLEngine::GetInstance();
	FMyOpenGLEngine &MyEngine = *MyEnginePtr;
	MyEngine.glfwInitialSetup();

	if (!MyEngine.glfwCreateWindowContext())
	{
		return -1;
	}

	if (!MyEngine.gladInitialization())
	{
		return -1;
	}
	
	//glViewport(0, 0, 800, 600);

	UTexture2D MyTextureWood;
	MyTextureWood.LoadFromFile("Resource/container.jpg");
	MyTextureWood.LoadTexture();

	UTexture2D MyTextureFace;
	MyTextureFace.LoadFromFile("Resource/awesomeface.png");
	MyTextureFace.LoadTexture();

	// shader program
	UMaterial MyShaderProgram;
	MyShaderProgram.SetupVertexShader("GLSL/vertex.vs");
	MyShaderProgram.SetupFragmentShader("GLSL/yellowfrag.fs");
	MyShaderProgram.SetupShaderProgram();
	MyShaderProgram.SetTexture(0, &MyTextureWood);
	MyShaderProgram.SetTexture(1, &MyTextureFace);

	UMyObjectMesh *MyMesh1 = new UMyObjectMesh();
	MyMesh1->CreateMeshSection(0, {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,

		//0.5f, -0.5f, 0.0f,
		//-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	}, {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f},
	{
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
	},
	{
		0,1,2,
		1,2,3
	});
	MyMesh1->GenRenderBuffer();
	MyMesh1->SetupShaderProgram(&MyShaderProgram);
	
	UMaterial MyShaderProgram2;
	MyShaderProgram2.SetupVertexShader("GLSL/vertex.vs");
	MyShaderProgram2.SetupFragmentShader("GLSL/yellowfrag.fs");
	MyShaderProgram2.SetupShaderProgram();

	UMyObjectMesh *MyMesh2 = new UMyObjectMesh();
	MyMesh2->CreateMeshSection(0, {
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	}, {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	}, {},  {});
	MyMesh2->GenRenderBuffer();
	//MyMesh2->SetupShaderProgram(&MyShaderProgram2);

	MyEngine.RenderLoop();

	return 0;
}