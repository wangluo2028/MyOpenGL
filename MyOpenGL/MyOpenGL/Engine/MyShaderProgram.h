#pragma once

#include "Texture/Texture2D.h"

class UMaterial
{
public:
	UMaterial();

	~UMaterial();

	unsigned int GetID();

	bool SetupVertexShader(const char* vertexShaderFile);

	bool SetupFragmentShader(const char* fragmentShaderFile);

	bool SetupShaderProgram();

	void UseShaderProgram();

	void SetTexture(size_t Index, UTexture2D *InTexture);

	void SetObjectColor(glm::vec3 InObjectColor);

	const glm::vec3& GetObjectColor();

protected:
	std::string ReadStringFromFile(const char *FilePath);

protected:
	unsigned int vertexShader;

	unsigned int fragmentShader;

	unsigned int shaderProgram;

	std::vector<UTexture2D*> Textures;

	glm::vec3 ObjectColor;
};

