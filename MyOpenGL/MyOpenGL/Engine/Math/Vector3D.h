#pragma once
class FVector
{
public:
	FVector();
	~FVector();

	FVector(float InX, float InY, float InZ);

	FVector& operator+=(const FVector &Other);

	FVector& operator-=(const FVector &Other);

	glm::vec3 ToGlmVector();

	float X;
	float Y;
	float Z;
};

FVector operator+(const FVector &First, const FVector &Second);