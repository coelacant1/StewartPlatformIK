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
	double basePlateRadius;//rb
	double baseMountingAngle;//ab
	double platformPlateRadius;//rp
	double platformMountingAngle;//ap
	double baseHeight;
	double baseActuatorLength;
	double maximumLength;

public:
	StewartPlatform() {}
	StewartPlatform(double basePlateRadius, double baseMountingAngle, double platformPlateRadius, double platformMountingAngle, double baseHeight, double maximumLength);

	void setBaseActuatorLength(double length);

	ActuatorLengths calculateIK(Vector3D XYZ);
	ActuatorLengths calculateIK(Vector3D XYZ, EulerAngles YPR);
	std::string actuatorOffsetVectorToString();
	std::string actuatorVectorsToString();
	std::string baseVectorsToString();
	std::string plateVectorsToString();
};
