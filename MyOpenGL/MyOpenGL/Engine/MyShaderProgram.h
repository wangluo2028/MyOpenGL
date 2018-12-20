#pragma once

class FMyShaderProgram
{
public:
	FMyShaderProgram();

	~FMyShaderProgram();

	unsigned int GetID();

	bool SetupVertexShader(const char* vertexShaderFile);

	bool SetupFragmentShader(const char* fragmentShaderFile);

	bool SetupShaderProgram();

	void UseShaderProgram();

protected:
	std::string ReadStringFromFile(const char *FilePath);

protected:
	unsigned int vertexShader;

	unsigned int fragmentShader;

	unsigned int shaderProgram;
};

