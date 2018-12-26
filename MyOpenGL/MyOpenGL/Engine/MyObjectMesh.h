#pragma once

#include "MyShaderProgram.h"
#include "Math/ProcMeshSection.h"

class UMyObjectMesh
{
public:
	UMyObjectMesh();
	~UMyObjectMesh();

	void CreateMeshSection(unsigned int Index, const std::vector<float> &InVertices, const std::vector<float> &InVertexColors,
		const std::vector<float> &InUVs,
		const std::vector<unsigned int> &InIndices);

	void SetupShaderProgram(class UMaterial *InShaderProgram);

	void SetTransform(const glm::mat4 &InTransform);

	void GenRenderBuffer();

	void Render();

protected:
	virtual void BeginPlay();

protected:
	std::vector<FProcMeshSection> ProcMeshSections;

	unsigned int VAO; // vertex array object
	unsigned int VBO; // vertex buffer object

	unsigned int EBO; // element buffer object

	class UMaterial *MyShaderProgram;

	glm::mat4 Transform2World;
};

