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

	// shader program
	FMyShaderProgram MyShaderProgram;
	MyShaderProgram.SetupVertexShader("GLSL/vertex.vs");
	MyShaderProgram.SetupFragmentShader("GLSL/frag.fs");
	MyShaderProgram.SetupShaderProgram();

	UMyObjectMesh *MyMesh1 = new UMyObjectMesh({
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,

		/*0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,*/
	});
	MyMesh1->GenVAOAndVBO();
	MyMesh1->SetupShaderProgram(&MyShaderProgram);
	MyEngine.GetWorld()->AddMesh(MyMesh1);


	FMyShaderProgram MyShaderProgram2;
	MyShaderProgram2.SetupVertexShader("GLSL/vertex.vs");
	MyShaderProgram2.SetupFragmentShader("GLSL/yellowfrag.fs");
	MyShaderProgram2.SetupShaderProgram();

	UMyObjectMesh *MyMesh2 = new UMyObjectMesh({
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	});
	MyMesh2->GenVAOAndVBO();
	MyMesh2->SetupShaderProgram(&MyShaderProgram2);
	MyEngine.GetWorld()->AddMesh(MyMesh2);

	MyEngine.RenderLoop();

	return 0;
}