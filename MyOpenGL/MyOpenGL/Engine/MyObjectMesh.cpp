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

void UMyObjectMesh::CreateMesh(const std::vector<float> &InVertices, const std::vector<float> &InVertexColors,
	const std::vector<unsigned int> &InIndices)
{
	Vertices = InVertices;

	Indices = InIndices;

	VertexColors = InVertexColors;

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

	std::vector<float> VertexDatas;
	size_t vertexCnt = Vertices.size() / 3;
	for (size_t i = 0; i < vertexCnt; ++i)
	{
		VertexDatas.push_back(Vertices[3*i]);
		VertexDatas.push_back(Vertices[3 * i + 1]);
		VertexDatas.push_back(Vertices[3 * i + 2]);

		if (!VertexColors.empty())
		{
			VertexDatas.push_back(VertexColors[3 * i]);
			VertexDatas.push_back(VertexColors[3 * i + 1]);
			VertexDatas.push_back(VertexColors[3 * i + 2]);
		}
	}

	glBufferData(GL_ARRAY_BUFFER, VertexDatas.size() * sizeof(float), VertexDatas.data(), GL_STATIC_DRAW);

	if (!Indices.empty())
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);
	}
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	if (!VertexColors.empty())
	{
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
}

unsigned int UMyObjectMesh::GetObjectID() const
{
	return VAO;
}

void UMyObjectMesh::Render()
{
	if (MyShaderProgram)
	{
		float greenColor = 0.5f * sin(glfwGetTime()) + 0.5f;

		MyShaderProgram->UseShaderProgram();

		//int ColorInFragLocation = glGetUniformLocation(MyShaderProgram->GetID(), "ColorInFragment");
		//glUniform4f(ColorInFragLocation, .0f, greenColor, .0f, 1.0f);
		//glProgramUniform4f(MyShaderProgram->GetID(), ColorInFragLocation, 1.0f, 0.0f, 0.0f, 1.0f);
	}

	glBindVertexArray(VAO);

	if (Indices.empty())
	{
		glDrawArrays(GL_TRIANGLES, 0, (int)Vertices.size());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, (int)Indices.size(), GL_UNSIGNED_INT, 0);
	}
	
}

void UMyObjectMesh::BeginPlay()
{
	FMyOpenGLEngine::GetInstance()->GetWorld()->AddMesh(this);
}
