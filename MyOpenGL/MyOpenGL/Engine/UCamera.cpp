#include "stdafx.h"
#include "UCamera.h"


UCamera::UCamera()
{
	CameraPos = FVector(0.0f, 0.0f, 3.0f);

	ViewTarget = FVector(0.0f, 0.0f, 0.0f);

	UpVector = FVector(0.0f, 1.0f, 0.0f);
}


UCamera::~UCamera()
{
}

glm::mat4 UCamera::GetViewMat()
{
	return glm::lookAt(CameraPos, ViewTarget, UpVector);
}
