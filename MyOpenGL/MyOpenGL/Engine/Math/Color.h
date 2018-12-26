#pragma once
class FColor
{
public:
	FColor();
	~FColor();

	FColor(float InR, float InG, float InB, float InA = 1.0f);

	float R;
	float G;
	float B;
	float A;
};

