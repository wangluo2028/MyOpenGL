#pragma once

#include "MyObjectMesh.h"

class UMyWorld
{
public:
	UMyWorld();
	~UMyWorld();

	void AddMesh(UMyObjectMesh *InMesh);

	const std::vector<UMyObjectMesh*>& GetMeshesInWorld();

protected:
	std::vector<UMyObjectMesh*> MyObjectMeshes;
};

