#pragma once

#include "Vector.h"

typedef struct DirectionAngle {
public:
	double Rotation = 0.0;
	Vector3D Direction;

	DirectionAngle(double rotation, double x, double y, double z);
	DirectionAngle(double rotation, Vector3D direction);

	std::string ToString();
} DirectionAngle;