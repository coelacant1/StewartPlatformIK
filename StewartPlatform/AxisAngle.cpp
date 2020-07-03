#include "AxisAngle.h"

AxisAngle::AxisAngle(double rotation, double x, double y, double z) {
	Rotation = rotation;
	Axis = Vector3D(x, y, z);
}

AxisAngle::AxisAngle(double rotation, Vector3D axis) {
	Rotation = rotation;
	Axis = axis;
}

std::string AxisAngle::ToString() {
	std::string r = Mathematics::DoubleToCleanString(Rotation);
	std::string x = Mathematics::DoubleToCleanString(Axis.X);
	std::string y = Mathematics::DoubleToCleanString(Axis.Y);
	std::string z = Mathematics::DoubleToCleanString(Axis.Z);

	return r + ": [" + x + " " + y + " " + z + "]";
}