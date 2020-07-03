#pragma once

#include "Mathematics.h"
#include "Vector.h"

typedef struct RotationMatrix {
private:
	Vector3D InitialVector;
	bool didRotate;
	std::vector<std::vector<double>> hMatrix;

	Vector3D ConvertCoordinateToVector();
	void ReadjustMatrix();
	void Rotate(Vector3D rotation);
	void RotateX(double theta);
	void RotateY(double theta);
	void RotateZ(double theta);
	void RotateRelative(RotationMatrix rM);

public:
	Vector3D XAxis;
	Vector3D YAxis;
	Vector3D ZAxis;

	RotationMatrix(Vector3D axes);
	RotationMatrix(Vector3D X, Vector3D Y, Vector3D Z);
	
	RotationMatrix Normalize();
	RotationMatrix Transpose();
	RotationMatrix Inverse();
	RotationMatrix Multiply(double d);
	RotationMatrix Multiply(RotationMatrix rM);

	bool IsEqual(RotationMatrix rM);
	double Determinant();

	static Vector3D RotateVector(Vector3D rotate, Vector3D coordinates);

	std::string ToString();

	RotationMatrix operator =(RotationMatrix rM) {
		this->XAxis = rM.XAxis;
		this->YAxis = rM.YAxis;
		this->ZAxis = rM.ZAxis;

		return *this;
	}
} RotationMatrix;