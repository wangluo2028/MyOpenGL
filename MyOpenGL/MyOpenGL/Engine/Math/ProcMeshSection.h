#pragma once

#include <vector>
#include "ProcMeshVertex.h"

class FProcMeshSection
{
public:
	FProcMeshSection();
	~FProcMeshSection();

	std::vector<FProcMeshVertex> ProcVertexBuffer;
	std::vector<unsigned int> ProcIndexBuffer;
};

