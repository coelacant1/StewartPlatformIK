#include "StewartPlatform.h"
#include <iostream>

StewartPlatform sP = StewartPlatform(500.0, 10.0, 500.0, 10.0, 930.0, 450.0);

int main() {
	ActuatorLengths aL = sP.calculateIK(Vector3D(0, 0, 100));

	std::cout << aL.ToString() << std::endl << std::endl;
	std::cout << sP.actuatorOffsetVectorToString() << std::endl << std::endl;
	std::cout << sP.actuatorVectorsToString() << std::endl << std::endl;
	std::cout << sP.baseVectorsToString() << std::endl << std::endl;
	std::cout << sP.plateVectorsToString() << std::endl << std::endl;
	std::cout << aL.constraintSuccess << std::endl << std::endl;


	aL = sP.calculateIK(Vector3D(50, 50, 200), EulerAngles(Vector3D(0, 20, 10), EulerConstants::EulerOrderXYZS));//Change to relative rotation

	std::cout << aL.ToString() << std::endl << std::endl;
	std::cout << sP.actuatorOffsetVectorToString() << std::endl << std::endl;
	std::cout << sP.actuatorVectorsToString() << std::endl << std::endl;
	std::cout << sP.baseVectorsToString() << std::endl << std::endl;
	std::cout << sP.plateVectorsToString() << std::endl << std::endl;
	std::cout << aL.constraintSuccess << std::endl << std::endl;

	return 0;
}