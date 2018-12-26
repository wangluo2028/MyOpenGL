#pragma once

#include "Vector3D.h"
#include "Vector2D.h"
#include "Color.h"

class FProcMeshVertex
{
public:
	FProcMeshVertex();
	~FProcMeshVertex();

	FVector Position;
	FColor Color;
	FVector2D UV;
};

