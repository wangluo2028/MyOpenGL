#pragma once

#include "MyShaderProgram.h"

class UMyObjectMesh
{
public:
	UMyObjectMesh(const std::vector<float> &InVertices);
	~UMyObjectMesh();

	void SetupShaderProgram(class FMyShaderProgram *InShaderProgram);

	void GenVAOAndVBO();

	unsigned int GetObjectID() const;

	void Render();

protected:
	std::vector<float> Vertices;

	unsigned int VAO;
	unsigned int VBO;

	class FMyShaderProgram *MyShaderProgram;
};

