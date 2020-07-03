#include "StewartPlatform.h"
#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
	if (argc == 7) {
		double br, bm, pr, pm, bh, ml, x, y, z, ya, pi, ro;

		br = std::stod(std::string(argv[1]));
		bm = std::stod(std::string(argv[2]));
		pr = std::stod(std::string(argv[3]));
		pm = std::stod(std::string(argv[4]));
		bh = std::stod(std::string(argv[5]));
		ml = std::stod(std::string(argv[6]));


		StewartPlatform sP = StewartPlatform(br, bm, pr, pm, bh, ml);// StewartPlatform(500.0, 10.0, 500.0, 10.0, 930.0, 450.0);

		while (true) {
			std::string line;
			std::getline(std::cin, line);

			std::stringstream lineStream(line);

			std::string token;

			lineStream >> token;
			x = std::stod(token);

			lineStream >> token;
			y = std::stod(token);

			lineStream >> token;
			z = std::stod(token);

			lineStream >> token;
			ya = std::stod(token);

			lineStream >> token;
			pi = std::stod(token);

			lineStream >> token;
			ro = std::stod(token);

			ActuatorLengths aL = sP.calculateIK(Vector3D(x, y, z), EulerAngles(Vector3D(ya, pi, ro), EulerConstants::EulerOrderXYZS));//Change to relative rotation
			std::cout << aL.ToString() << std::endl;
		}
	}
	else {
		std::cout << "ERROR: Incorrect number of arguments " << argc << " of " << 7 << '.' << std::endl;
	}

	return 0;
}