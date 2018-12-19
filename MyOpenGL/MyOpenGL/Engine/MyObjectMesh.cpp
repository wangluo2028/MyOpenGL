#include "stdafx.h"
#include "MyObjectMesh.h"
#include "MyOpenGLEngine.h"

UMyObjectMesh::UMyObjectMesh()
{
	VAO = 0;
	VBO = 0;

	EBO = 0;
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

void UMyObjectMesh::CreateMesh(const std::vector<float> &InVertices, const std::vector<unsigned int> &InIndices)
{
	Vertices = InVertices;

	Indices = InIndices;

	VAO = 0;
	VBO = 0;

	EBO = 0;
}

void UMyObjectMesh::SetupShaderProgram(class FMyShaderProgram *InShaderProgram)
{
	MyShaderProgram = InShaderProgram;

	BeginPlay();
}

void UMyObjectMesh::GenRenderBuffer()
{
	// vertex buffer object
	glGenBuffers(1, &VBO);

	// vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
}

unsigned int UMyObjectMesh::GetObjectID() const
{
	return VAO;
}

void UMyObjectMesh::Render()
{
	if (MyShaderProgram)
	{
		MyShaderProgram->UseShaderProgram();
	}
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, (int)Vertices.size());
	glDrawElements(GL_TRIANGLES, (int)Indices.size(), GL_UNSIGNED_INT, 0);
}

void UMyObjectMesh::BeginPlay()
{
	FMyOpenGLEngine::GetInstance()->GetWorld()->AddMesh(this);
}
