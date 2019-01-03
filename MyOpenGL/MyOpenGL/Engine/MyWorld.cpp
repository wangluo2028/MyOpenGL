#include "stdafx.h"
#include "MyWorld.h"


UMyWorld::UMyWorld()
{
}


UMyWorld::~UMyWorld()
{
	for (UMyObjectMesh *MyMesh : GetMeshesInWorld())
	{
		delete MyMesh;
	}
}

void UMyWorld::AddMesh(UMyObjectMesh *InMesh)
{
	MyObjectMeshes.push_back(InMesh);
}

void UMyWorld::AddLight(ULightMesh *InLight)
{
	LightMeshes.push_back(InLight);
	MyObjectMeshes.push_back(InLight);
}

const std::vector<UMyObjectMesh*>& UMyWorld::GetMeshesInWorld()
{
	return MyObjectMeshes;
}

const std::vector<ULightMesh*>& UMyWorld::GetLightsInWorld()
{
	return LightMeshes;
}
