#include "stdafx.h"
#include "MyObjectMesh.h"
#include "MyOpenGLEngine.h"

UMyObjectMesh::UMyObjectMesh()
{
	VAO = 0;
	VBO = 0;

	EBO = 0;

	Transform2World = glm::identity<glm::mat4>();
	/*Transform2World = glm::rotate(Transform2World, glm::radians(90.0f), glm::vec3(0, 0, 1.0f));
	Transform2World = glm::scale(Transform2World, glm::vec3(0.5f, 0.5f, 0.0f));*/
	//Transform2World = glm::translate(Transform2World, glm::vec3(0.5f, 0.5f, 0.0f));
}

UMyObjectMesh::~UMyObjectMesh()
{
	// A VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER. 
	// This also means it stores its unbind calls so make sure you don't unbind the element array buffer before unbinding your VAO, 
	// otherwise it doesn't have an EBO configured.
	glDeleteVertexArrays(1, &VAO);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void UMyObjectMesh::CreateMeshSection(unsigned int Index, const std::vector<float> &InVertices, const std::vector<float> &InVertexColors,
	const std::vector<float> &InUVs,
	const std::vector<unsigned int> &InIndices)
{
	if ((Index + 1) > ProcMeshSections.size())
	{
		ProcMeshSections.resize(Index + 1);
	}

	FProcMeshSection &ProcMeshSection = ProcMeshSections[Index];
	size_t VertexCnt = InVertices.size() / 3;
	ProcMeshSection.ProcVertexBuffer.resize(VertexCnt);
	size_t VertexColorCnt = InVertexColors.size() / 3;
	size_t UVCnt = InUVs.size() / 2;
	for (size_t VertexIndex = 0; VertexIndex < VertexCnt; ++VertexIndex)
	{
		FProcMeshVertex &ProcVertex = ProcMeshSection.ProcVertexBuffer[VertexIndex];
		ProcVertex.Position = FVector(InVertices[3 * VertexIndex], InVertices[3 * VertexIndex + 1], 
			InVertices[3 * VertexIndex + 2]);

		if (VertexIndex < VertexColorCnt)
		{
			ProcVertex.Color = FColor(InVertexColors[3 * VertexIndex], InVertexColors[3 * VertexIndex + 1], 
				InVertexColors[3 * VertexIndex + 2]);
		}

		if (VertexIndex < UVCnt)
		{
			ProcVertex.UV = FVector2D(InUVs[2 * VertexIndex], InUVs[2 * VertexIndex + 1]);
		}
	}

	ProcMeshSection.ProcIndexBuffer = InIndices;

	VAO = 0;
	VBO = 0;

	EBO = 0;
}

void UMyObjectMesh::SetupShaderProgram(class UMaterial *InShaderProgram)
{
	MyShaderProgram = InShaderProgram;

	BeginPlay();
}

void UMyObjectMesh::SetTransform(const glm::mat4 &InTransform)
{
	Transform2World = InTransform;
}

void UMyObjectMesh::GenRenderBuffer()
{
	if (ProcMeshSections.size() < 1)
	{
		return;
	}

	FProcMeshSection& ProcMeshSection = ProcMeshSections[0];

	// vertex buffer object
	glGenBuffers(1, &VBO);

	// vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, ProcMeshSection.ProcVertexBuffer.size() * sizeof(FProcMeshVertex), ProcMeshSection.ProcVertexBuffer.data(), GL_STATIC_DRAW);

	if (!ProcMeshSection.ProcIndexBuffer.empty())
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ProcMeshSection.ProcIndexBuffer.size() * sizeof(unsigned int), ProcMeshSection.ProcIndexBuffer.data(), GL_STATIC_DRAW);
	}
	
	glVertexAttribPointer(0, sizeof(FVector) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(FProcMeshVertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, sizeof(FColor) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(FProcMeshVertex), (void*)(offsetof(FProcMeshVertex, Color)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, sizeof(FVector2D) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(FProcMeshVertex), (void*)(offsetof(FProcMeshVertex, UV)));
	glEnableVertexAttribArray(2);
}

void UMyObjectMesh::Render()
{
	if (MyShaderProgram)
	{
		MyShaderProgram->UseShaderProgram();
	}

	glBindVertexArray(VAO);

	//glm::mat4 ViewMat = glm::identity<glm::mat4>();
	//ViewMat = glm::translate(ViewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	//glm::mat4 ViewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 1.0f, 0.0f));
	float Radius = 10.0f;
	glm::mat4 ViewMat = glm::lookAt(glm::vec3(Radius*cos(glfwGetTime()), 0.0, Radius*sin(glfwGetTime())),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));


	glm::mat4 ProjectionMat = glm::identity<glm::mat4>();
	ProjectionMat = glm::perspective(glm::radians(45.0f), (float)FMyOpenGLEngine::windowWidth / FMyOpenGLEngine::windowHeight, 0.1f, 100.0f);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	for (unsigned int i = 0; i < 10; ++i)
	{
		Transform2World = glm::identity<glm::mat4>();
		Transform2World = glm::translate(Transform2World, cubePositions[i]);
		float RotationAngle = 20.0f * i;
		Transform2World = glm::rotate(Transform2World, RotationAngle, glm::vec3(0.5f, 1.0f, 0.0f));
		//Transform2World = glm::rotate(Transform2World, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		//Transform2World = glm::translate(Transform2World, glm::vec3(0.5f, -0.5f, 0.0f));
		//Transform2World = glm::rotate(Transform2World, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		Transform2World = ProjectionMat * ViewMat *Transform2World;

		glUniformMatrix4fv(glGetUniformLocation(MyShaderProgram->GetID(), "ObjectTransform"), 1, GL_FALSE, glm::value_ptr(Transform2World));

		if (ProcMeshSections.size() < 1)
		{
			return;
		}

		FProcMeshSection& ProcMeshSection = ProcMeshSections[0];
		if (ProcMeshSection.ProcIndexBuffer.empty())
		{
			glDrawArrays(GL_TRIANGLES, 0, (int)ProcMeshSection.ProcVertexBuffer.size());
		}
		else
		{
			glDrawElements(GL_TRIANGLES, (int)ProcMeshSection.ProcIndexBuffer.size(), GL_UNSIGNED_INT, 0);
		}
	}
}

void UMyObjectMesh::BeginPlay()
{
	FMyOpenGLEngine::GetInstance()->GetWorld()->AddMesh(this);
}
