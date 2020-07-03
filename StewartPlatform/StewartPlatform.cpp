#include "StewartPlatform.h"

StewartPlatform::StewartPlatform(double basePlateRadius, double baseMountingAngle, double platformPlateRadius, double platformMountingAngle, double baseHeight, double maximumLength) {
	this->basePlateRadius = basePlateRadius;
	this->baseMountingAngle = baseMountingAngle;
	this->platformPlateRadius = platformPlateRadius;
	this->platformMountingAngle = platformMountingAngle;

	B1 = Vector3D(basePlateRadius * cos((baseMountingAngle / 2.0) * Mathematics::PI / 180.0), -basePlateRadius * sin((baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B2 = Vector3D(basePlateRadius * cos((baseMountingAngle / 2.0) * Mathematics::PI / 180.0), basePlateRadius * sin((baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B3 = Vector3D(-basePlateRadius * cos((60.0 + baseMountingAngle / 2.0) * Mathematics::PI / 180.0), basePlateRadius * sin((60.0 + baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B4 = Vector3D(-basePlateRadius * cos((60.0 - baseMountingAngle / 2.0) * Mathematics::PI / 180.0), basePlateRadius * sin((60.0 - baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B5 = Vector3D(-basePlateRadius * cos((60.0 - baseMountingAngle / 2.0) * Mathematics::PI / 180.0), -basePlateRadius * sin((60.0 - baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B6 = Vector3D(-basePlateRadius * cos((60.0 + baseMountingAngle / 2.0) * Mathematics::PI / 180.0), -basePlateRadius * sin((60.0 + baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);

	P1 = Vector3D(platformPlateRadius * cos((60.0 - platformMountingAngle / 2.0) * Mathematics::PI / 180.0), -platformPlateRadius * sin((60.0 - platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P2 = Vector3D(platformPlateRadius * cos((60.0 - platformMountingAngle / 2.0) * Mathematics::PI / 180.0), platformPlateRadius * sin((60.0 - platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P3 = Vector3D(platformPlateRadius * cos((60.0 + platformMountingAngle / 2.0) * Mathematics::PI / 180.0), platformPlateRadius * sin((60.0 + platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P4 = Vector3D(-platformPlateRadius * cos((platformMountingAngle / 2.0) * Mathematics::PI / 180.0), platformPlateRadius * sin((platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P5 = Vector3D(-platformPlateRadius * cos((platformMountingAngle / 2.0) * Mathematics::PI / 180.0), -platformPlateRadius * sin((platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P6 = Vector3D(platformPlateRadius * cos((60.0 + platformMountingAngle / 2.0) * Mathematics::PI / 180.0), -platformPlateRadius * sin((60.0 + platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);

	this->baseHeight = baseHeight;
	this->maximumLength = maximumLength;
	baseActuatorLength = 0;// = StewartPlatform::calculateIK(Vector3D(0, 0, 0)).U;
}

void StewartPlatform::setBaseActuatorLength(double baseActuatorLength) {
	this->baseActuatorLength = baseActuatorLength;
}

ActuatorLengths StewartPlatform::calculateIK(Vector3D XYZ) {
	XYZ.Z += baseHeight;

	L1 = P1 + XYZ - B1;
	L2 = P2 + XYZ - B2;
	L3 = P3 + XYZ - B3;
	L4 = P4 + XYZ - B4;
	L5 = P5 + XYZ - B5;
	L6 = P6 + XYZ - B6;

	bool withinConstraints = L1.Magnitude() - baseActuatorLength > 0 && L1.Magnitude() - baseActuatorLength < maximumLength &&
		L2.Magnitude() - baseActuatorLength > 0 && L2.Magnitude() - baseActuatorLength < maximumLength &&
		L3.Magnitude() - baseActuatorLength > 0 && L3.Magnitude() - baseActuatorLength < maximumLength &&
		L4.Magnitude() - baseActuatorLength > 0 && L4.Magnitude() - baseActuatorLength < maximumLength &&
		L5.Magnitude() - baseActuatorLength > 0 && L5.Magnitude() - baseActuatorLength < maximumLength &&
		L6.Magnitude() - baseActuatorLength > 0 && L6.Magnitude() - baseActuatorLength < maximumLength;

	return ActuatorLengths(L1.Magnitude() - baseActuatorLength, L2.Magnitude() - baseActuatorLength, L3.Magnitude() - baseActuatorLength, L4.Magnitude() - baseActuatorLength, L5.Magnitude() - baseActuatorLength, L6.Magnitude() - baseActuatorLength, withinConstraints);
}

ActuatorLengths StewartPlatform::calculateIK(Vector3D XYZ, EulerAngles YPR) {
	XYZ.Z += baseHeight;

	Quaternion q = Rotation(YPR).GetQuaternion();

	L1 = q.RotateVector(P1) + XYZ - B1;
	L2 = q.RotateVector(P2) + XYZ - B2;
	L3 = q.RotateVector(P3) + XYZ - B3;
	L4 = q.RotateVector(P4) + XYZ - B4;
	L5 = q.RotateVector(P5) + XYZ - B5;
	L6 = q.RotateVector(P6) + XYZ - B6;

	bool withinConstraints = L1.GetLength() - baseActuatorLength > 0 && L1.GetLength() - baseActuatorLength < maximumLength &&
		L2.GetLength() - baseActuatorLength > 0 && L2.GetLength() - baseActuatorLength < maximumLength &&
		L3.GetLength() - baseActuatorLength > 0 && L3.GetLength() - baseActuatorLength < maximumLength &&
		L4.GetLength() - baseActuatorLength > 0 && L4.GetLength() - baseActuatorLength < maximumLength &&
		L5.GetLength() - baseActuatorLength > 0 && L5.GetLength() - baseActuatorLength < maximumLength &&
		L6.GetLength() - baseActuatorLength > 0 && L6.GetLength() - baseActuatorLength < maximumLength;

	return ActuatorLengths(L1.GetLength() - baseActuatorLength, L2.GetLength() - baseActuatorLength, L3.GetLength() - baseActuatorLength, L4.GetLength() - baseActuatorLength, L5.GetLength() - baseActuatorLength, L6.GetLength() - baseActuatorLength, withinConstraints);
}

std::string StewartPlatform::actuatorOffsetVectorToString() {
	return Actuators(L1 + B1, L2 + B2, L3 + B3, L4 + B4, L5 + B5, L6 + B6).ToString();
}

std::string StewartPlatform::actuatorVectorsToString() {
	return Actuators(L1, L2, L3, L4, L5, L6).ToString();
}

std::string StewartPlatform::baseVectorsToString() {
	return Actuators(B1, B2, B3, B4, B5, B6).ToString();
}

std::string StewartPlatform::plateVectorsToString() {
	return Actuators(P1, P2, P3, P4, P5, P6).ToString();
}
