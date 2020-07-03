#include "Quaternion.h"

Quaternion::Quaternion() {
	this->W = 1.0;
	this->X = 0.0;
	this->Y = 0.0;
	this->Z = 0.0;
}

Quaternion::Quaternion(const Quaternion& quaternion) {
	this->W = quaternion.W;
	this->X = quaternion.X;
	this->Y = quaternion.Y;
	this->Z = quaternion.Z;
}

Quaternion::Quaternion(Vector3D vector) {
	this->W = 0;
	this->X = vector.X;
	this->Y = vector.Y;
	this->Z = vector.Z;
}

Quaternion::Quaternion(double w, double x, double y, double z) {
	this->W = w;
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Vector3D Quaternion::RotateVector(Vector3D coordinate) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
	Quaternion qv = Quaternion(0, coordinate.X, coordinate.Y, coordinate.Z);
	Quaternion qr = current * qv * current.MultiplicativeInverse();

	return Vector3D {
		qr.X,
		qr.Y,
		qr.Z
	};
}

Vector3D Quaternion::UnrotateVector(Vector3D coordinate) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return current.Conjugate().RotateVector(coordinate);
}

Vector3D Quaternion::GetBiVector() {
	return Vector3D{
		this->X,
		this->Y,
		this->Z
	};
}

Quaternion Quaternion::SphericalInterpolation(Quaternion q1, Quaternion q2, double ratio) {
	q1 = q1.UnitQuaternion();
	q2 = q2.UnitQuaternion();

	double dot = q1.DotProduct(q2);//Cosine between the two quaternions

	if (dot < 0.0)//Shortest path correction
	{
		q1 = q1.AdditiveInverse();
		dot = -dot;
	}

	if (dot > 0.999)//Linearly interpolates if results are close
	{
		return (q1.Add( (q2.Subtract(q1)).Multiply(ratio) )).UnitQuaternion();
	}
	else
	{
		dot = Mathematics::Constrain(dot, -1, 1);

		double theta0 = acos(dot);
		double theta = theta0 * ratio;

		//Quaternion q3 = (q2.Subtract(q1.Multiply(dot))).UnitQuaternion();//UQ for orthonomal 
		double f1 = cos(theta) - dot * sin(theta) / sin(theta0);
		double f2 = sin(theta) / sin(theta0);

		return q1.Multiply(f1).Add(q2.Multiply(f2)).UnitQuaternion();
	}
}

Quaternion Quaternion::Add(Quaternion quaternion) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion {
		current.W + quaternion.W,
		current.X + quaternion.X,
		current.Y + quaternion.Y,
		current.Z + quaternion.Z
	};
}

Quaternion Quaternion::Subtract(Quaternion quaternion) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion{
		current.W - quaternion.W,
		current.X - quaternion.X,
		current.Y - quaternion.Y,
		current.Z - quaternion.Z
	};
}

Quaternion Quaternion::Multiply(Quaternion quaternion) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
	
	return Quaternion
	{
		current.W * quaternion.W - current.X * quaternion.X - current.Y * quaternion.Y - current.Z * quaternion.Z,
		current.W * quaternion.X + current.X * quaternion.W + current.Y * quaternion.Z - current.Z * quaternion.Y,
		current.W * quaternion.Y - current.X * quaternion.Z + current.Y * quaternion.W + current.Z * quaternion.X,
		current.W * quaternion.Z + current.X * quaternion.Y - current.Y * quaternion.X + current.Z * quaternion.W
	};
}

Quaternion Quaternion::Multiply(double scalar) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion{
		current.W * scalar,
		current.X * scalar,
		current.Y * scalar,
		current.Z * scalar
	};
}

Quaternion operator  *(double scalar, Quaternion q) {
	Quaternion quaternion = Quaternion(q.W, q.X, q.Y, q.Z);

	return quaternion.Multiply(scalar);
}

Quaternion operator  *(Quaternion q, double scalar) {
	Quaternion quaternion = Quaternion(q.W, q.X, q.Y, q.Z);

	return quaternion.Multiply(scalar);
}

Quaternion Quaternion::Divide(Quaternion quaternion) {
	double scale = quaternion.W * quaternion.W + quaternion.X * quaternion.X + quaternion.Y * quaternion.Y + quaternion.Z * quaternion.Z;
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		( current.W * quaternion.W + current.X * quaternion.X + current.Y * quaternion.Y + current.Z * quaternion.Z) / scale,
		(-current.W * quaternion.X + current.X * quaternion.W + current.Y * quaternion.Z - current.Z * quaternion.Y) / scale,
		(-current.W * quaternion.Y - current.X * quaternion.Z + current.Y * quaternion.W + current.Z * quaternion.X) / scale,
		(-current.W * quaternion.Z + current.X * quaternion.Y - current.Y * quaternion.X + current.Z * quaternion.W) / scale
	};
}

Quaternion Quaternion::Divide(double scalar) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		current.W / scalar,
		current.X / scalar,
		current.Y / scalar,
		current.Z / scalar
	};
}

Quaternion Quaternion::Power(Quaternion exponent) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		pow(current.W, exponent.W),
		pow(current.X, exponent.X),
		pow(current.Y, exponent.Y),
		pow(current.Z, exponent.Z)
	};
}

Quaternion Quaternion::Power(double exponent) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		pow(current.W, exponent),
		pow(current.X, exponent),
		pow(current.Y, exponent),
		pow(current.Z, exponent)
	};
}

Quaternion Quaternion::Permutate(Vector3D permutation) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);
	double perm[3];

	perm[(int)permutation.X] = current.X;
	perm[(int)permutation.Y] = current.Y;
	perm[(int)permutation.Z] = current.Z;

	current.X = perm[0];
	current.Y = perm[1];
	current.Z = perm[2];

	return current;
}

Quaternion Quaternion::Absolute() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		std::abs(current.W),
		std::abs(current.X),
		std::abs(current.Y),
		std::abs(current.Z)
	};
}

Quaternion Quaternion::AdditiveInverse() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		-current.W,
		-current.X,
		-current.Y,
		-current.Z
	};
}

Quaternion Quaternion::MultiplicativeInverse() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return current.Conjugate().Multiply(1.0 / current.Normal());

}

Quaternion Quaternion::Conjugate() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Quaternion
	{
		 current.W,
		-current.X,
		-current.Y,
		-current.Z
	};
}

Quaternion Quaternion::UnitQuaternion() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	double n = current.Normal();

	current.W = current.W / n;
	current.X = current.X / n;
	current.Y = current.Y / n;
	current.Z = current.Z / n;

	return current;
}

double Quaternion::Magnitude() {
	return sqrt(Normal());
}

double Quaternion::DotProduct(Quaternion q) {
	return (W * q.W) + (X * q.X) + (Y * q.Y) + (Z * q.Z);
}

double Quaternion::Normal() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);


	return pow(current.W, 2.0) + pow(current.X, 2.0) + pow(current.Y, 2.0) + pow(current.Z, 2.0);
}

bool Quaternion::IsNaN() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Mathematics::IsNaN(current.W) || Mathematics::IsNaN(current.X) || Mathematics::IsNaN(current.Y) || Mathematics::IsNaN(current.Z);
}

bool Quaternion::IsFinite() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Mathematics::IsInfinite(current.W) || Mathematics::IsInfinite(current.X) || Mathematics::IsInfinite(current.Y) || Mathematics::IsInfinite(current.Z);
}

bool Quaternion::IsInfinite() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return Mathematics::IsFinite(current.W) || Mathematics::IsFinite(current.X) || Mathematics::IsFinite(current.Y) || Mathematics::IsFinite(current.Z);
}

bool Quaternion::IsNonZero() {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return current.W != 0 && current.X != 0 && current.Y != 0 && current.Z != 0;
}

bool Quaternion::IsEqual(Quaternion quaternion) {
	Quaternion current = Quaternion(this->W, this->X, this->Y, this->Z);

	return !current.IsNaN() && !quaternion.IsNaN() &&
		current.W == quaternion.W &&
		current.X == quaternion.X &&
		current.Y == quaternion.Y &&
		current.Z == quaternion.Z;
}

std::string Quaternion::ToString() {
	std::string w = Mathematics::DoubleToCleanString(this->W);
	std::string x = Mathematics::DoubleToCleanString(this->X);
	std::string y = Mathematics::DoubleToCleanString(this->Y);
	std::string z = Mathematics::DoubleToCleanString(this->Z);
	
	return "[" + w + ", " + x + ", " + y + ", " + z + "]";
	
}
