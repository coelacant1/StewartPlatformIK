#pragma once

#include "Mathematics.h"
#include "Vector.h"

typedef struct Quaternion {
public:
	double W = 1.0;
	double X = 0.0;
	double Y = 0.0;
	double Z = 0.0;

	Quaternion();
	Quaternion(const Quaternion& quaternion);
	Quaternion(Vector3D vector);
	Quaternion(double W, double X, double Y, double Z);

	Vector3D RotateVector(Vector3D coordinate);
	Vector3D UnrotateVector(Vector3D coordinate);
	Vector3D GetBiVector();

	Quaternion Add(Quaternion quaternion);
	Quaternion Subtract(Quaternion quaternion);
	Quaternion Multiply(Quaternion quaternion);
	Quaternion Multiply(double scalar);
	Quaternion Divide(Quaternion quaternion);
	Quaternion Divide(double scalar);
	Quaternion Power(Quaternion quaternion);

	Quaternion Power(double exponent);
	Quaternion Permutate(Vector3D permutation);

	Quaternion Absolute();
	Quaternion AdditiveInverse();
	Quaternion MultiplicativeInverse();
	Quaternion Conjugate();
	Quaternion UnitQuaternion();

	double Magnitude();
	double DotProduct(Quaternion quaternion);
	double Normal();

	bool IsNaN();
	bool IsFinite();
	bool IsInfinite();
	bool IsNonZero();
	bool IsEqual(Quaternion quaternion);

	std::string ToString();

	//Static functions
	static Quaternion SphericalInterpolation(Quaternion q1, Quaternion q2, double ratio);

	static Quaternion Add(Quaternion q1, Quaternion q2) {
		return q1.Add(q2);
	}

	static Quaternion Subtract(Quaternion q1, Quaternion q2) {
		return q1.Subtract(q2);
	}

	static Quaternion Multiply(Quaternion q1, Quaternion q2) {
		return q1.Multiply(q2);
	}

	static Quaternion Divide(Quaternion q1, Quaternion q2) {
		return q1.Divide(q2);
	}

	static Quaternion Power(Quaternion q1, Quaternion q2) {
		return q1.Power(q2);
	}

	static double DotProduct(Quaternion q1, Quaternion q2) {
		return q1.DotProduct(q2);
	}


	static Quaternion Power(Quaternion quaternion, double exponent) {
		return quaternion.Power(exponent);
	}

	static Quaternion Permutate(Quaternion quaternion, Vector3D vector) {
		return quaternion.Permutate(vector);
	}

	static Quaternion Absolute(Quaternion quaternion) {
		return quaternion.Absolute();
	}

	static Quaternion AdditiveInverse(Quaternion quaternion) {
		return quaternion.AdditiveInverse();
	}

	static Quaternion MultiplicativeInverse(Quaternion quaternion) {
		return quaternion.MultiplicativeInverse();
	}

	static Quaternion Conjugate(Quaternion quaternion) {
		return quaternion.Conjugate();
	}

	static Quaternion UnitQuaternion(Quaternion quaternion) {
		return quaternion.UnitQuaternion();
	}

	static double Magnitude(Quaternion quaternion) {
		return quaternion.Magnitude();
	}

	static double Normal(Quaternion quaternion) {
		return quaternion.Normal();
	}

	//Operator overloads
	bool operator ==(Quaternion quaternion) {
		return this->IsEqual(quaternion);
	}

	bool operator !=(Quaternion quaternion) {
		return !(this->IsEqual(quaternion));
	}

	Quaternion operator =(Quaternion quaternion) {
		this->W = quaternion.W;
		this->X = quaternion.X;
		this->Y = quaternion.Y;
		this->Z = quaternion.Z;
		
		return quaternion;
	}

	Quaternion operator  +(Quaternion quaternion) {
		Quaternion q = Quaternion(*this);

		return q.Add(quaternion);
	}

	Quaternion operator  -(Quaternion quaternion) {
		Quaternion q = Quaternion(*this);

		return q.Subtract(quaternion);
	}

	Quaternion operator  *(Quaternion quaternion) {
		Quaternion q = Quaternion(*this);

		return q.Multiply(quaternion);
	}

	Quaternion operator  /(Quaternion quaternion) {
		Quaternion q = Quaternion(*this);

		return q.Divide(quaternion);
	}


	Quaternion operator  /(double value) {
		Quaternion q = Quaternion(*this);

		return q.Divide(value);
	}

	friend Quaternion operator *(double scalar, Quaternion q);
	friend Quaternion operator *(Quaternion q, double scalar);
} Quaternion;
