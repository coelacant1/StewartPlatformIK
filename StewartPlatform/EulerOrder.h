#pragma once

#include "Vector.h"

typedef struct EulerOrder {
public:
	enum Axis
	{
		X,
		Y,
		Z
	};

	enum Parity
	{
		Even,
		Odd
	};

	enum AxisRepetition
	{
		Yes,
		No
	};

	enum AxisFrame
	{
		Static,
		Rotating
	};

	Axis InitialAxis;
	Parity AxisPermutation;
	AxisRepetition InitialAxisRepetition;
	AxisFrame FrameTaken;
	Vector3D Permutation;

	EulerOrder();
	EulerOrder(Axis axis, Parity parity, AxisRepetition axisRepetition, AxisFrame axisFrame, Vector3D permutation);
	std::string ToString();
} EulerOrder;