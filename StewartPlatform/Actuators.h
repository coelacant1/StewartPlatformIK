#pragma once

#include "Vector.h"

struct Actuators {
	Vector3D U;
	Vector3D V;
	Vector3D W;
	Vector3D X;
	Vector3D Y;
	Vector3D Z;

	Actuators() {}
	Actuators(Vector3D U, Vector3D V, Vector3D W, Vector3D X, Vector3D Y, Vector3D Z) : U{ U }, V{ V }, W{ W }, X{ X }, Y{ Y }, Z{ Z } {}

	std::string ToString() {
		return	U.ToString() + std::string("\n") +
				V.ToString() + std::string("\n") +
				W.ToString() + std::string("\n") +
				X.ToString() + std::string("\n") +
				Y.ToString() + std::string("\n") +
				Z.ToString();
	}
};
