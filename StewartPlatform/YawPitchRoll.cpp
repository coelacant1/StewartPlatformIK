#include "YawPitchRoll.h"

YawPitchRoll::YawPitchRoll() {
	this->Yaw = 0.0;
	this->Pitch = 0.0;
	this->Roll = 0.0;
}

YawPitchRoll::YawPitchRoll(Vector3D vector) {
	this->Yaw = vector.X;
	this->Pitch = vector.Y;
	this->Roll = vector.Z;
}

YawPitchRoll::YawPitchRoll(const YawPitchRoll& ypr) {
	this->Yaw = ypr.Yaw;
	this->Pitch = ypr.Pitch;
	this->Roll = ypr.Roll;
}

YawPitchRoll::YawPitchRoll(double yaw, double pitch, double roll) {
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->Roll = roll;
}

std::string YawPitchRoll::ToString() {
	std::string y = Mathematics::DoubleToCleanString(this->Yaw);
	std::string p = Mathematics::DoubleToCleanString(this->Pitch);
	std::string r = Mathematics::DoubleToCleanString(this->Roll);

	return "[" + y + ", " + p + ", " + r + "]";
}
