#include "stdafx.h"
#include "MyObjectMesh.h"


UMyObjectMesh::UMyObjectMesh(const std::vector<float> &InVertices)
{
	Vertices = InVertices;

	VAO = 0;
	VBO = 0;
}

UMyObjectMesh::~UMyObjectMesh()
{
}

void UMyObjectMesh::SetupShaderProgram(class FMyShaderProgram *InShaderProgram)
{
	MyShaderProgram = InShaderProgram;
}

void UMyObjectMesh::GenVAOAndVBO()
{
	// vertex buffer object
	glGenBuffers(1, &VBO);

	// vertex array object
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);
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
	glDrawArrays(GL_TRIANGLES, 0, (int)Vertices.size());
}
