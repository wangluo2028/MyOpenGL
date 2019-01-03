#include "stdafx.h"
#include "Camera.h"

const float MOVESPEED = 2.5f;
const float MOUSESPEED = 0.1f;
const float ZOOMSPEED = 1.0f;

// default camera values
const float YAW = -90.0f;
//const float YAW = 0.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

UCamera::UCamera(const glm::vec3 &InCameraPos)
	:CameraPos(InCameraPos)
{
	Front = Up = Right = glm::vec3(0.0f, 0.0f, 0.0f);

	WorldUpVector = glm::vec3(0.0f, 1.0f, 0.0f);

	Yaw = YAW;
	Pitch = PITCH;
	Zoom = ZOOM;

	UpdateCameraVector();
}


UCamera::~UCamera()
{
}

glm::mat4 UCamera::GetViewMat()
{
	return glm::lookAt(CameraPos, (CameraPos + Front), Up);
}

float UCamera::GetZoomScale()
{
	return Zoom;
}

void UCamera::ProcessKeyboardInput(EDirection CameraDir, float DeltaTime)
{
	float Velocity = MOVESPEED * DeltaTime;
	switch (CameraDir)
	{
	case EFront:
	{
		CameraPos += Front * Velocity;
	}
		break;
	case EBack:
	{
		CameraPos -= Front * Velocity;
	}
		break;
	case ELeft:
	{
		CameraPos -= Right * Velocity;
	}
		break;
	case ERight:
	{
		CameraPos += Right * Velocity;
	}
		break;
	default:
		break;
	}
}

void UCamera::ProcessMouseInput(float DeltaX, float DeltaY, bool bInConstrainPitch)
{
	DeltaX *= MOUSESPEED;
	DeltaY *= MOUSESPEED;

	Yaw += DeltaX;
	Pitch += DeltaY;

	if (bInConstrainPitch)
	{
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}

		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}
	}

	UpdateCameraVector();
}

void UCamera::ProcessMouseScroll(float Offset)
{
	Offset *= ZOOMSPEED;
	if (Zoom >= 1.0f && Zoom <= 45.0f)
	{
		Zoom -= Offset;
	}
	if (Zoom <= 1.0f)
	{
		Zoom = 1.0f;
	}
	if (Zoom >= 45.0f)
	{
		Zoom = 45.0f;
	}
}

void UCamera::UpdateCameraVector()
{
	Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front.y = sin(glm::radians(Pitch));
	Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(Front);
	Right = glm::normalize(glm::cross(Front, WorldUpVector));
	Up = glm::normalize(glm::cross(Right, Front));
}
