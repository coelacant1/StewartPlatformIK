#pragma once

#include "Vector.h"

typedef struct YawPitchRoll {
private:

public:
	double Yaw;
	double Pitch;
	double Roll;

	YawPitchRoll();
	YawPitchRoll(Vector3D vector);
	YawPitchRoll(const YawPitchRoll& ypr);
	YawPitchRoll(double yaw, double pitch, double roll);

	std::string ToString();
} YawPitchRoll;