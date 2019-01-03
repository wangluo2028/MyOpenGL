#include "stdafx.h"
#include "LightMesh.h"
#include "MyOpenGLEngine.h"

ULightMesh::ULightMesh()
{
}


ULightMesh::~ULightMesh()
{
}

void ULightMesh::BeginPlay()
{
	FMyOpenGLEngine::GetInstance()->GetWorld()->AddLight(this);
}
