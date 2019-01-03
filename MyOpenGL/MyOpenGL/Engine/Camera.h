#pragma once

#include "Math/Vector3D.h"

enum EDirection
{
	EFront,
	EBack,
	ELeft,
	ERight,
};

class UCamera
{
public:
	UCamera(const glm::vec3 &InCameraPos = glm::vec3(0.0f, 0.0f, 3.0f));
	~UCamera();

	glm::mat4 GetViewMat();

	float GetZoomScale();

	void ProcessKeyboardInput(EDirection CameraDir, float DeltaTime);

	void ProcessMouseInput(float DeltaX, float DeltaY, bool bInConstrainPitch = true);

	void ProcessMouseScroll(float Offset);

protected:
	void UpdateCameraVector();

protected:
	glm::vec3 CameraPos;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;

	glm::vec3 WorldUpVector;

	float Yaw;
	float Pitch;
	float Zoom;
};

