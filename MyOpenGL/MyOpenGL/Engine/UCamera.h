#pragma once

class UCamera
{
public:
	UCamera();
	~UCamera();

	glm::mat4 GetViewMat();



protected:
	FVector CameraPos;
	FVector ViewTarget;
	FVector UpVector;
};

