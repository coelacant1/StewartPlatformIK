#pragma once

#include "Vector.h"

typedef struct DirectionAngle {
public:
	double Rotation;
	Vector3D Direction;

	DirectionAngle(double rotation, double x, double y, double z);
	DirectionAngle(double rotation, Vector3D direction);

	std::string ToString();
} DirectionAngle;