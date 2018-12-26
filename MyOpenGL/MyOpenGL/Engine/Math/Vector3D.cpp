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

FVector::~FVector()
{
}
