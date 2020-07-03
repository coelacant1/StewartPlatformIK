#include "StewartPlatform.h"
#include <iostream>

using namespace std;

StewartPlatform sP;

int main() {
	sP = StewartPlatform(500.0, 10.0, 500.0, 10.0, 500.0, 500.0);

	ActuatorLengths aL = sP.calculateIK(Vector3D(0, 0, 100));

	std::cout << aL.ToString() << std::endl << std::endl; 
	std::cout << sP.actuatorOffsetVectorToString() << std::endl << std::endl;
	std::cout << sP.actuatorVectorsToString() << std::endl << std::endl;
	std::cout << sP.baseVectorsToString() << std::endl << std::endl;
	std::cout << sP.plateVectorsToString() << std::endl << std::endl;


	aL = sP.calculateIK(Vector3D(0, 0, 100), EulerAngles(Vector3D(45, 0, 45), EulerConstants::EulerOrderXYZS));//Change to relative rotation

	std::cout << aL.ToString() << std::endl << std::endl;
	std::cout << sP.actuatorOffsetVectorToString() << std::endl << std::endl;
	std::cout << sP.actuatorVectorsToString() << std::endl << std::endl;
	std::cout << sP.baseVectorsToString() << std::endl << std::endl;
	std::cout << sP.plateVectorsToString() << std::endl << std::endl;

	std::cout << Vector3D(212, 366, 0).GetLength() << std::endl;

	return 0;
}