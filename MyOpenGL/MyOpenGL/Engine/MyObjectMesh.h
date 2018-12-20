#pragma once

#include "MyShaderProgram.h"

class UMyObjectMesh
{
public:
	UMyObjectMesh();
	~UMyObjectMesh();

	void CreateMesh(const std::vector<float> &InVertices, const std::vector<float> &InVertexColors,
		const std::vector<unsigned int> &InIndices);

	void SetupShaderProgram(class FMyShaderProgram *InShaderProgram);

	void GenRenderBuffer();

	unsigned int GetObjectID() const;

	void Render();

protected:
	virtual void BeginPlay();

protected:
	std::vector<float> Vertices;

	std::vector<unsigned int> Indices;

	std::vector<float> VertexColors;

	unsigned int VAO; // vertex array object
	unsigned int VBO; // vertex buffer object

	unsigned int EBO; // element buffer object

	class FMyShaderProgram *MyShaderProgram;
};

