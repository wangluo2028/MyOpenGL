#include "stdafx.h"
#include "Vector3D.h"


FVector::FVector()
{
	X = Y = Z = 0.0f;
}


FVector::FVector(float InX, float InY, float InZ)
	:X(InX), Y(InY), Z(InZ)
{

}

FVector& FVector::operator+=(const FVector &Other)
{
	*this = (*this) + Other;

	return *this;
}

FVector& FVector::operator-=(const FVector &Other)
{
	*this = (*this) + FVector(-Other.X, -Other.Y, -Other.Z);
	return *this;
}

glm::vec3 FVector::ToGlmVector()
{
	return glm::vec3(X, Y, Z);
}

FVector::~FVector()
{
}

FVector operator+(const FVector &First, const FVector &Second)
{
	return FVector(First.X + Second.X, First.Y + Second.Y, First.Z + Second.Z);
}
