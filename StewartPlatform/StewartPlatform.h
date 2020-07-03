#pragma once
#include "Vector.h"
#include "Rotation.h"
#include "Actuators.h"

#include "ActuatorLengths.h"

class StewartPlatform {
private:
	ActuatorLengths aL;
	Vector3D B1, B2, B3, B4, B5, B6;
	Vector3D P1, P2, P3, P4, P5, P6;
	Vector3D L1, L2, L3, L4, L5, L6;
	double basePlateRadius = 0.0;//rb
	double baseMountingAngle = 0.0;//ab
	double platformPlateRadius = 0.0;//rp
	double platformMountingAngle = 0.0;//ap
	double baseHeight = 0.0;
	double baseActuatorLength = 0.0;
	double maximumLength = 0.0;

public:
	StewartPlatform() {}
	StewartPlatform(double basePlateRadius, double baseMountingAngle, double platformPlateRadius, double platformMountingAngle, double baseHeight, double maximumLength);

	ActuatorLengths calculateIK(Vector3D XYZ);
	ActuatorLengths calculateIK(Vector3D XYZ, EulerAngles YPR);
	std::string actuatorOffsetVectorToString();
	std::string actuatorVectorsToString();
	std::string baseVectorsToString();
	std::string plateVectorsToString();
};
