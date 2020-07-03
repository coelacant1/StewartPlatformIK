#pragma once

#include "Vector.h"

typedef struct YawPitchRoll {
private:

public:
	double Yaw = 0.0;
	double Pitch = 0.0;
	double Roll = 0.0;

	YawPitchRoll();
	YawPitchRoll(Vector3D vector);
	YawPitchRoll(const YawPitchRoll& ypr);
	YawPitchRoll(double yaw, double pitch, double roll);

	std::string ToString();
} YawPitchRoll;