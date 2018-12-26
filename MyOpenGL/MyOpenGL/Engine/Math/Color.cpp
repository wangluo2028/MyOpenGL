#include "stdafx.h"
#include "Color.h"


FColor::FColor()
{
	R = G = B = A = 0.0f;
}

FColor::FColor(float InR, float InG, float InB, float InA)
	:R(InR), G(InG), B(InB), A(InA)
{

}

FColor::~FColor()
{
}
