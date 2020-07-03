#include "Vector.h"

Vector3D::Vector3D() {
	this->X = 0.0;
	this->Y = 0.0;
	this->Z = 0.0;
}

Vector3D::Vector3D(const Vector3D& vector) {
	this->X = vector.X;
	this->Y = vector.Y;
	this->Z = vector.Z;
}

Vector3D::Vector3D(double X, double Y, double Z) {
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

Vector3D Vector3D::Absolute() {
	return Vector3D{
		std::abs(this->X),
		std::abs(this->Y),
		std::abs(this->Z)
	};
}

Vector3D Vector3D::Normal() {
	return Multiply(this->Magnitude() == 0 ? std::numeric_limits<double>::infinity() : 1 / this->Magnitude());
}

Vector3D Vector3D::Add(Vector3D vector) {
	return Vector3D{
		this->X + vector.X,
		this->Y + vector.Y,
		this->Z + vector.Z 
	};
}

Vector3D Vector3D::Subtract(Vector3D vector) {
	return Vector3D {
		this->X - vector.X,
		this->Y - vector.Y,
		this->Z - vector.Z 
	};
}

Vector3D Vector3D::Multiply(Vector3D vector) {
	return Vector3D {
		this->X * vector.X,
		this->Y * vector.Y,
		this->Z * vector.Z 
	};
}

Vector3D Vector3D::Divide(Vector3D vector) {
	return Vector3D {
		this->X / vector.X,
		this->Y / vector.Y,
		this->Z / vector.Z 
	};
}

Vector3D Vector3D::Multiply(double scalar) {
	return Vector3D {
		this->X * scalar,
		this->Y * scalar,
		this->Z * scalar 
	};
}

Vector3D Vector3D::Divide(double scalar) {
	return Vector3D {
		this->X / scalar,
		this->Y / scalar,
		this->Z / scalar
	};

}

Vector3D Vector3D::CrossProduct(Vector3D vector) {
	return Vector3D {
		(this->Y * vector.Z) - (this->Z * vector.Y),
		(this->Z * vector.X) - (this->X * vector.Z),
		(this->X * vector.Y) - (this->Y * vector.X) 
	};
}

Vector3D Vector3D::UnitSphere() {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);
	double length = vector.GetLength();

	if (length == 1) return vector;
	if (length == 0) return Vector3D(0, 1, 0);

	return Vector3D {
		vector.X / length,
		vector.Y / length,
		vector.Z / length 
	};
}

Vector3D Vector3D::Constrain(double minimum, double maximum) {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);

	vector.X = Mathematics::Constrain(X, minimum, maximum);
	vector.Y = Mathematics::Constrain(Y, minimum, maximum);
	vector.Z = Mathematics::Constrain(Z, minimum, maximum);

	return vector;
}

Vector3D Vector3D::Constrain(Vector3D minimum, Vector3D maximum) {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);

	vector.X = Mathematics::Constrain(X, minimum.X, maximum.X);
	vector.Y = Mathematics::Constrain(Y, minimum.Y, maximum.Y);
	vector.Z = Mathematics::Constrain(Z, minimum.Z, maximum.Z);

	return vector;
}

double Vector3D::Magnitude() {
	Vector3D vector = Vector3D(this->X, this->Y, this->Z);

	return sqrt(DotProduct(vector, vector));
}

double Vector3D::GetLength() {
	return sqrt(pow(this->X, 2) + pow(this->Y, 2) + pow(this->Z, 2));
}

double Vector3D::DotProduct(Vector3D vector) {
	return (this->X * vector.X) + (this->Y * vector.Y) + (this->Z * vector.Z);
}

double Vector3D::CalculateEuclideanDistance(Vector3D vector) {
	return sqrt(pow(this->X - vector.X, 2) + pow(this->Y - vector.Y, 2) + pow(this->Z - vector.Z, 2));
}

bool Vector3D::IsEqual(Vector3D vector) {
	return (this->X == vector.X) && (this->Y == vector.Y) && (this->Z == vector.Z);
}

std::string Vector3D::ToString() {
	std::string x = Mathematics::DoubleToCleanString(this->X);
	std::string y = Mathematics::DoubleToCleanString(this->Y);
	std::string z = Mathematics::DoubleToCleanString(this->Z);

	return "[" + x + ", " + y + ", " + z + "]";
}
