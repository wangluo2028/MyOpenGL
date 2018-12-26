#include "stdafx.h"
#include "Vector2D.h"


FVector2D::FVector2D()
{
	X = Y = 0.0f;
}


FVector2D::FVector2D(float InX, float InY)
	:X(InX), Y(InY)
{

}

FVector2D::~FVector2D()
{
}
