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

void UMyObjectMesh::BeginPlay()
{
	FMyOpenGLEngine::GetInstance()->GetWorld()->AddMesh(this);
}
