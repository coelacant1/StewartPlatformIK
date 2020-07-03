#pragma once

#include "Mathematics.h"

typedef struct Vector3D {
public:
	double X = 0.0;
	double Y = 0.0;
	double Z = 0.0;

	Vector3D();
	Vector3D(const Vector3D& vector);
	Vector3D(double x, double y, double z);
	Vector3D Absolute();
	Vector3D Normal();
	Vector3D Add(Vector3D vector);
	Vector3D Subtract(Vector3D vector);
	Vector3D Multiply(Vector3D vector);
	Vector3D Divide(Vector3D vector);
	Vector3D Multiply(double scalar);
	Vector3D Divide(double scalar);
	Vector3D CrossProduct(Vector3D vector);
	Vector3D UnitSphere();//unit sphere
	Vector3D Constrain(double minimum, double maximum);
	Vector3D Constrain(Vector3D minimum, Vector3D maximum);

	double Magnitude();
	double GetLength();
	double DotProduct(Vector3D vector);
	double CalculateEuclideanDistance(Vector3D vector);
	bool IsEqual(Vector3D vector);
	std::string ToString();

	static Vector3D DegreesToRadians(Vector3D degrees) {
		return degrees / (180.0 / Mathematics::PI);
	}

	static Vector3D RadiansToDegrees(Vector3D radians) {
		return radians * (180.0 / Mathematics::PI);
	}

	//Static function declaractions
	static Vector3D Normal(Vector3D vector) {
		return vector.Normal();
	}

	static Vector3D Add(Vector3D v1, Vector3D v2) {
		return v1.Add(v2);
	}

	static Vector3D Subtract(Vector3D v1, Vector3D v2) {
		return v1.Subtract(v2);
	}

	static Vector3D Multiply(Vector3D v1, Vector3D v2) {
		return v1.Multiply(v2);
	}

	static Vector3D Divide(Vector3D v1, Vector3D v2) {
		return v1.Divide(v2);
	}

	static Vector3D Multiply(Vector3D vector, double scalar) {
		return vector.Multiply(scalar);
	}

	static Vector3D Multiply(double scalar, Vector3D vector) {
		return vector.Multiply(scalar);
	}

	static Vector3D Divide(Vector3D vector, double scalar) {
		return vector.Divide(scalar);
	}

	static Vector3D CrossProduct(Vector3D v1, Vector3D v2) {
		return v1.CrossProduct(v2);
	}

	static double DotProduct(Vector3D v1, Vector3D v2) {
		return v1.DotProduct(v2);
	}

	static double CalculateEuclideanDistance(Vector3D v1, Vector3D v2) {
		return v1.CalculateEuclideanDistance(v2);
	}

	static bool IsEqual(Vector3D v1, Vector3D v2) {
		return v1.IsEqual(v2);
	}

	//Operator overloads
	bool operator ==(Vector3D vector) {
		return this->IsEqual(vector);
	}

	bool operator !=(Vector3D vector) {
		return !(this->IsEqual(vector));
	}

	Vector3D operator  =(Vector3D vector) {
		this->X = vector.X;
		this->Y = vector.Y;
		this->Z = vector.Z;

		return *this;
	}

	Vector3D operator  +(Vector3D vector) {
		Vector3D v = Vector3D(*this);

		return v.Add(vector);
	}

	Vector3D operator  -(Vector3D vector) {
		Vector3D v = Vector3D(*this);

		return v.Subtract(vector);
	}

	Vector3D operator  *(Vector3D vector) {
		Vector3D v = Vector3D(*this);

		return v.Multiply(vector);
	}

	Vector3D operator  /(Vector3D vector) {
		Vector3D v = Vector3D(*this);

		return v.Divide(vector);
	}

	Vector3D operator  *(double value) {
		Vector3D v = Vector3D(*this);

		return v.Multiply(value);
	}

	Vector3D operator  /(double value) {
		Vector3D v = Vector3D(*this);

		return v.Divide(value);
	}
} Vector3D;
