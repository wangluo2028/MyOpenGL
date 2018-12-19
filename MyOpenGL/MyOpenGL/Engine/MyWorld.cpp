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

const std::vector<UMyObjectMesh*>& UMyWorld::GetMeshesInWorld()
{
	return MyObjectMeshes;
}
