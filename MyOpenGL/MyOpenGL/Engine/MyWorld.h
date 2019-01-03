#pragma once

#include "LightMesh.h"

class UMyWorld
{
public:
	UMyWorld();
	~UMyWorld();

	void AddMesh(UMyObjectMesh *InMesh);

	void AddLight(ULightMesh *InLight);

	const std::vector<UMyObjectMesh*>& GetMeshesInWorld();

	const std::vector<ULightMesh*>& GetLightsInWorld();

protected:
	std::vector<UMyObjectMesh*> MyObjectMeshes;

	std::vector<ULightMesh*> LightMeshes;
};

