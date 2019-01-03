#pragma once

#include "MyObjectMesh.h"

class ULightMesh : public UMyObjectMesh
{
public:
	ULightMesh();
	~ULightMesh();

protected:
	virtual void BeginPlay();
};

