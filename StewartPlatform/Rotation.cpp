#include "Rotation.h"

Rotation::Rotation() {
	QuaternionRotation = Quaternion();
}

Rotation::Rotation(Quaternion quaternion) {
	QuaternionRotation = quaternion;
}

Rotation::Rotation(AxisAngle axisAngle) {
	QuaternionRotation = AxisAngleToQuaternion(axisAngle);
}

Rotation::Rotation(DirectionAngle directionAngle) {
	QuaternionRotation = DirectionAngleToQuaternion(directionAngle);
}

Rotation::Rotation(RotationMatrix rotationMatrix) {
	QuaternionRotation = RotationMatrixToQuaternion(rotationMatrix);
}

Rotation::Rotation(EulerAngles eulerAngles) {
	QuaternionRotation = EulerAnglesToQuaternion(eulerAngles);
}

Rotation::Rotation(Vector3D initial, Vector3D target) {
	QuaternionRotation = QuaternionFromDirectionVectors(initial, target);
}

Rotation::Rotation(YawPitchRoll ypr) {
	QuaternionRotation = YawPitchRollToQuaternion(ypr);
}

Quaternion Rotation::AxisAngleToQuaternion(AxisAngle axisAngle) {
		double rotation = Mathematics::DegreesToRadians(axisAngle.Rotation);
		double scale = sin(rotation / 2.0);

		return Quaternion(
			cos(rotation / 2.0),
			axisAngle.Axis.X * scale,
			axisAngle.Axis.Y * scale,
			axisAngle.Axis.Z * scale
		);
}

Quaternion Rotation::DirectionAngleToQuaternion(DirectionAngle directionAngle) {
	Vector3D right =   Vector3D(1, 0, 0);
	Vector3D up =      Vector3D(0, 1, 0);
	Vector3D forward = Vector3D(0, 0, 1);

	directionAngle.Direction.UnitSphere();

	Vector3D rotatedRight;
	Vector3D rotatedUp = Vector3D(directionAngle.Direction);
	Vector3D rotatedForward;

	Quaternion rotationChange = QuaternionFromDirectionVectors(up, rotatedUp);

	Vector3D rightAngleRotated = RotationMatrix::RotateVector(Vector3D(0, -directionAngle.Rotation, 0), right);
	Vector3D forwardAngleRotated = RotationMatrix::RotateVector(Vector3D(0, -directionAngle.Rotation, 0), forward);

	rotatedRight = rotationChange.RotateVector(rightAngleRotated);
	rotatedForward = rotationChange.RotateVector(forwardAngleRotated);

	return RotationMatrixToQuaternion(RotationMatrix(rotatedRight, rotatedUp, rotatedForward)).UnitQuaternion();
}

Quaternion Rotation::RotationMatrixToQuaternion(RotationMatrix rM) {
	Quaternion q = Quaternion();

	Vector3D X = Vector3D(rM.XAxis);
	Vector3D Y = Vector3D(rM.YAxis);
	Vector3D Z = Vector3D(rM.ZAxis);

	double matrixTrace = X.X + Y.Y + Z.Z;
	double square;

	if (matrixTrace > 0)//standard procedure
	{
		square = sqrt(1.0 + matrixTrace) * 2.0;//4 * qw

		q.W = 0.25 * square;
		q.X = (Z.Y - Y.Z) / square;
		q.Y = (X.Z - Z.X) / square;
		q.Z = (Y.X - X.Y) / square;
	}
	else if ((X.X > Y.Y) && (X.X > Z.Z))
	{
		square = sqrt(1.0 + X.X - Y.Y - Z.Z) * 2.0;//4 * qx

		q.W = (Z.Y - Y.Z) / square;
		q.X = 0.25 * square;
		q.Y = (X.Y + Y.X) / square;
		q.Z = (X.Z + Z.X) / square;
	}
	else if (Y.Y > Z.Z)
	{
		square = sqrt(1.0 + Y.Y - X.X - Z.Z) * 2.0;//4 * qy

		q.W = (X.Z - Z.X) / square;
		q.X = (X.Y + Y.X) / square;
		q.Y = 0.25 * square;
		q.Z = (Y.Z + Z.Y) / square;
	}
	else
	{
		square = sqrt(1.0 + Z.Z - X.X - Y.Y) * 2.0;//4 * qz

		q.W = (Y.X - X.Y) / square;
		q.X = (X.Z + Z.X) / square;
		q.Y = (Y.Z + Z.Y) / square;
		q.Z = 0.25 * square;
	}

	return q.UnitQuaternion().Conjugate();
}

Quaternion Rotation::EulerAnglesToQuaternion(EulerAngles eulerAngles) {
	Quaternion q = Quaternion(1, 0, 0, 0);
	double sx, sy, sz, cx, cy, cz, cc, cs, sc, ss;

	eulerAngles.Angles.X = Mathematics::DegreesToRadians(eulerAngles.Angles.X);
	eulerAngles.Angles.Y = Mathematics::DegreesToRadians(eulerAngles.Angles.Y);
	eulerAngles.Angles.Z = Mathematics::DegreesToRadians(eulerAngles.Angles.Z);

	if (eulerAngles.Order.FrameTaken == EulerOrder::AxisFrame::Rotating)
	{
		double t = eulerAngles.Angles.X;
		eulerAngles.Angles.X = eulerAngles.Angles.Z;
		eulerAngles.Angles.Z = t;
	}

	if (eulerAngles.Order.AxisPermutation == EulerOrder::Parity::Odd)
	{
		eulerAngles.Angles.Y = -eulerAngles.Angles.Y;
	}

	sx = sin(eulerAngles.Angles.X * 0.5);
	sy = sin(eulerAngles.Angles.Y * 0.5);
	sz = sin(eulerAngles.Angles.Z * 0.5);

	cx = cos(eulerAngles.Angles.X * 0.5);
	cy = cos(eulerAngles.Angles.Y * 0.5);
	cz = cos(eulerAngles.Angles.Z * 0.5);

	cc = cx * cz;
	cs = cx * sz;
	sc = sx * cz;
	ss = sx * sz;

	if (eulerAngles.Order.InitialAxisRepetition == EulerOrder::AxisRepetition::Yes)
	{
		q.X = cy * (cs + sc);
		q.Y = sy * (cc + ss);
		q.Z = sy * (cs - sc);
		q.W = cy * (cc - ss);
	}
	else
	{
		q.X = cy * sc - sy * cs;
		q.Y = cy * ss + sy * cc;
		q.Z = cy * cs - sy * sc;
		q.W = cy * cc + sy * ss;
	}

	q.Permutate(eulerAngles.Order.Permutation);

	if (eulerAngles.Order.AxisPermutation == EulerOrder::Parity::Odd)
	{
		q.Y = -q.Y;
	}

	return q;
}

Quaternion Rotation::YawPitchRollToQuaternion(YawPitchRoll ypr) {
	std::cout << "YPR to Quaternion not implemented." << std::endl;

	return Quaternion();
}

EulerAngles Rotation::RotationMatrixToEulerAngles(RotationMatrix rM, EulerOrder order) {
	EulerAngles eulerAngles = EulerAngles(Vector3D(0, 0, 0), order);
	//Vector3D p = order.Permutation;

	if (order.InitialAxisRepetition == EulerOrder::AxisRepetition::Yes)
	{
		double sy = sqrt(pow(rM.XAxis.Y, 2.0) + pow(rM.XAxis.Z, 2.0));

		if (sy > 32.0 * std::numeric_limits<double>::epsilon())//16 * float.Epsilon
		{
			eulerAngles.Angles.X = atan2(rM.XAxis.Y, rM.XAxis.Z);
			eulerAngles.Angles.Y = atan2(sy, rM.XAxis.X);
			eulerAngles.Angles.Z = atan2(rM.YAxis.X, -rM.ZAxis.X);
		}
		else
		{
			eulerAngles.Angles.X = atan2(-rM.YAxis.Z, rM.YAxis.Y);
			eulerAngles.Angles.Y = atan2(sy, rM.XAxis.X);
			eulerAngles.Angles.Z = 0;
		}
	}
	else
	{
		double cy = sqrt(pow(rM.XAxis.X, 2.0) + pow(rM.YAxis.X, 2.0));

		if (cy > 32.0 * std::numeric_limits<double>::epsilon())
		{
			eulerAngles.Angles.X = atan2( rM.ZAxis.Y, rM.ZAxis.Z);
			eulerAngles.Angles.Y = atan2(-rM.ZAxis.X, cy);
			eulerAngles.Angles.Z = atan2( rM.YAxis.X, rM.XAxis.X);
		}
		else
		{
			eulerAngles.Angles.X = atan2(-rM.YAxis.Z, rM.YAxis.Y);
			eulerAngles.Angles.Y = atan2(-rM.ZAxis.X, cy);
			eulerAngles.Angles.Z = 0;
		}
	}

	if (order.AxisPermutation == EulerOrder::Parity::Odd)
	{
		eulerAngles.Angles.X = -eulerAngles.Angles.X;
		eulerAngles.Angles.Y = -eulerAngles.Angles.Y;
		eulerAngles.Angles.Z = -eulerAngles.Angles.Z;
	}

	if (order.FrameTaken == EulerOrder::AxisFrame::Rotating)
	{
		double temp = eulerAngles.Angles.X;
		eulerAngles.Angles.X = eulerAngles.Angles.Z;
		eulerAngles.Angles.Z = temp;
	}

	eulerAngles.Angles.X = Mathematics::RadiansToDegrees(eulerAngles.Angles.X);
	eulerAngles.Angles.Y = Mathematics::RadiansToDegrees(eulerAngles.Angles.Y);
	eulerAngles.Angles.Z = Mathematics::RadiansToDegrees(eulerAngles.Angles.Z);

	return eulerAngles;
}

RotationMatrix Rotation::EulerAnglesToRotationMatrix(EulerAngles eulerAngles) {
	RotationMatrix rM = RotationMatrix(Vector3D(0, 0, 0));
	double sx, sy, sz, cx, cy, cz, cc, cs, sc, ss; 
	//Vector3D p = eulerAngles.Order.Permutation;

	eulerAngles.Angles.X = Mathematics::DegreesToRadians(eulerAngles.Angles.X);
	eulerAngles.Angles.Y = Mathematics::DegreesToRadians(eulerAngles.Angles.Y);
	eulerAngles.Angles.Z = Mathematics::DegreesToRadians(eulerAngles.Angles.Z);

	if (eulerAngles.Order.FrameTaken == EulerOrder::AxisFrame::Rotating)
	{
		double t = eulerAngles.Angles.X;
		eulerAngles.Angles.X = eulerAngles.Angles.Z;
		eulerAngles.Angles.Z = t;
	}

	if (eulerAngles.Order.AxisPermutation == EulerOrder::Parity::Odd)
	{
		eulerAngles.Angles.X = -eulerAngles.Angles.X;
		eulerAngles.Angles.Y = -eulerAngles.Angles.Y;
		eulerAngles.Angles.Z = -eulerAngles.Angles.Z;
	}

	sx = sin(eulerAngles.Angles.X);
	sy = sin(eulerAngles.Angles.Y);
	sz = sin(eulerAngles.Angles.Z);
	cx = cos(eulerAngles.Angles.X);
	cy = cos(eulerAngles.Angles.Y);
	cz = cos(eulerAngles.Angles.Z);

	cc = cx * cz;
	cs = cx * sz;
	sc = sx * cz;
	ss = sx * sz;

	if (eulerAngles.Order.InitialAxisRepetition == EulerOrder::AxisRepetition::Yes)
	{
		rM.XAxis.X = cy;       rM.XAxis.Y = sy * sx;       rM.XAxis.Z = sy * cx;
		rM.YAxis.X = sy * sz;  rM.YAxis.Y = -cy * ss + cc; rM.YAxis.Z = -cy * cs - sc;
		rM.ZAxis.X = -sy * cz; rM.ZAxis.Y = cy * sc + cs;  rM.ZAxis.Z = cy * cc - ss;
	}
	else
	{
		rM.XAxis.X = cy * cz;  rM.XAxis.Y = sy * sc - cs;  rM.XAxis.Z = sy * cc + ss;
		rM.YAxis.X = cy * sz;  rM.YAxis.Y = sy * ss + cc;  rM.YAxis.Z = sy * cs - sc;
		rM.ZAxis.X = -sy;      rM.ZAxis.Y = cy * sx;       rM.ZAxis.Z = cy * cx;
	}

	return rM;
}

Quaternion Rotation::QuaternionFromDirectionVectors(Vector3D initial, Vector3D target) {
	Quaternion q = Quaternion(1, 0, 0, 0);
	Vector3D tempV = Vector3D(0, 0, 0);
	Vector3D xAxis = Vector3D(1, 0, 0);
	Vector3D yAxis = Vector3D(0, 1, 0);

	double dot = Vector3D::DotProduct(initial, target);

	if (dot < -0.999999)
	{
		tempV = Vector3D::CrossProduct(xAxis, initial);

		if (tempV.GetLength() < 0.000001)
		{
			tempV = Vector3D::CrossProduct(yAxis, initial);
		}

		tempV = tempV.UnitSphere();

		q = Rotation(AxisAngle(Mathematics::PI, tempV)).GetQuaternion();
	}
	else if (dot > 0.999999)
	{
		q.W = 1.0;
		q.X = 0.0;
		q.Y = 0.0;
		q.Z = 0.0;
	}
	else
	{
		tempV = Vector3D::CrossProduct(initial, target);

		q.W = 1.0 + dot;
		q.X = tempV.X;
		q.Y = tempV.Y;
		q.Z = tempV.Z;

		q = q.UnitQuaternion();
	}

	return q;
}

Quaternion Rotation::GetQuaternion() {
	return QuaternionRotation;
}

AxisAngle Rotation::GetAxisAngle() {
	AxisAngle axisAngle = AxisAngle(0, 0, 1, 0);
	Quaternion q = QuaternionRotation;

	q = (std::abs(q.W) > 1.0) ? q.UnitQuaternion() : q;

	axisAngle.Rotation = Mathematics::RadiansToDegrees(2.0 * acos(q.W));

	double quaternionCheck = sqrt(1.0 - pow(q.W, 2.0));//Prevents rotation jumps, and division by zero

	if (quaternionCheck >= 0.001)//Prevents division by zero
	{
		//Normalizes axis
		axisAngle.Axis.X = q.X / quaternionCheck;
		axisAngle.Axis.Y = q.Y / quaternionCheck;
		axisAngle.Axis.Z = q.Z / quaternionCheck;
	}
	else
	{
		//If X is close to zero the axis doesn't matter
		axisAngle.Axis.X = 0.0;
		axisAngle.Axis.Y = 1.0;
		axisAngle.Axis.Z = 0.0;
	}

	return axisAngle;
}

DirectionAngle Rotation::GetDirectionAngle() {
	Quaternion q = QuaternionRotation.UnitQuaternion();
	Vector3D up = Vector3D(0, 1, 0);//up vector
	Vector3D right = Vector3D(1, 0, 0);
	Vector3D rotatedUp = q.RotateVector(up);//new direction vector
	Vector3D rotatedRight = q.RotateVector(right);
	Quaternion rotationChange = QuaternionFromDirectionVectors(up, rotatedUp);

	//rotate forward vector by direction vector rotation
	Vector3D rightXZCompensated = rotationChange.UnrotateVector(rotatedRight);//should only be two points on circle, compare against right

																			  //define angles that define the forward vector, and the rotated then compensated forward vector
	double rightAngle = Mathematics::RadiansToDegrees(atan2(right.Z, right.X));//forward as zero
	double rightRotatedAngle = Mathematics::RadiansToDegrees(atan2(rightXZCompensated.Z, rightXZCompensated.X));//forward as zero

																										 //angle about the axis defined by the direction of the object
	double angle = rightAngle - rightRotatedAngle;

	//returns the angle rotated about the rotated up vector as an axis
	return DirectionAngle(angle, rotatedUp);
}

RotationMatrix Rotation::GetRotationMatrix() {
	Vector3D X = Vector3D(1, 0, 0);
	Vector3D Y = Vector3D(0, 1, 0);
	Vector3D Z = Vector3D(0, 0, 1);

	return RotationMatrix(
		QuaternionRotation.RotateVector(X),
		QuaternionRotation.RotateVector(Y),
		QuaternionRotation.RotateVector(Z)
	);
}

EulerAngles Rotation::GetEulerAngles(EulerOrder order) {
	Quaternion q = Quaternion(QuaternionRotation);

	double norm = q.Normal();
	double scale = norm > 0.0 ? 2.0 / norm : 0.0;
	Vector3D X, Y, Z;

	Vector3D s = Vector3D(q.X * scale, q.Y * scale, q.Z * scale);
	Vector3D w = Vector3D(q.W * s.X, q.W * s.Y, q.W * s.Z);
	Vector3D x = Vector3D(q.X * s.X, q.X * s.Y, q.X * s.Z);
	Vector3D y = Vector3D(0.0, q.Y * s.Y, q.Y * s.Z);
	Vector3D z = Vector3D(0.0, 0.0, q.Z * s.Z);

	//0X, 1Y, 2Z, 3W
	X.X = 1.0 - (y.Y + z.Z);   Y.X = x.Y - w.Z;           Z.X = x.Z + w.Y;
	Y.X = x.Y + w.Z;           Y.Y = 1.0 - (x.X + z.Z);   Z.Y = y.Z - w.X;
	Z.X = x.Z - w.Y;           Y.Z = y.Z + w.X;           Z.Z = 1.0 - (x.X + y.Y);

	return RotationMatrixToEulerAngles(RotationMatrix(X, Y, Z), order);
}

YawPitchRoll Rotation::GetYawPitchRoll() {
	Quaternion q = QuaternionRotation;

	//EulerAngles ea = Rotation(q).GetEulerAngles(EulerConstants::EulerOrderZXZR);

	//ea.Angles;

	//intrinsic tait-bryan rotation of order XYZ
	double yaw =  atan2( 2.0 * (q.Y * q.Z + q.W * q.X), pow(q.W, 2) - pow(q.X, 2) - pow(q.Y, 2) + pow(q.Z, 2));
	double pitch = asin(-2.0 * (q.X * q.Z - q.W * q.Y));
	double roll = atan2( 2.0 * (q.X * q.Y + q.W * q.Z), pow(q.W, 2) + pow(q.X, 2) - pow(q.Y, 2) - pow(q.Z, 2));

	yaw = Mathematics::RadiansToDegrees(yaw);
	pitch = Mathematics::RadiansToDegrees(pitch);
	roll = Mathematics::RadiansToDegrees(roll);

	return YawPitchRoll(yaw, pitch, roll);
}