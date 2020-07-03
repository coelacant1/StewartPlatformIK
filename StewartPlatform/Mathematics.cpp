#include "Mathematics.h"

double Mathematics::PI = atan(1.0) * 4;

double Mathematics::Constrain(double value, double minimum, double maximum) {
	if (value > maximum)
	{
		value = maximum;
	}
	else if (value < minimum)
	{
		value = minimum;
	}

	return value;
}

double Mathematics::DegreesToRadians(double degrees) {
	return degrees / (180.0 / PI);
}

double Mathematics::RadiansToDegrees(double radians) {
	return radians * (180.0 / PI);
}

std::string Mathematics::DoubleToCleanString(double value) {
	std::stringstream stream;

	stream << std::fixed << std::setprecision(4) << std::setw(10) << value;

	return stream.str();
}

void Mathematics::CleanPrint(int values, ...) {
	va_list valueList;
	std::string printOut = "";

	va_start(valueList, values);

	for (int i = 0; i <= values; i++) {
		double value = va_arg(valueList, double);
		printOut += Mathematics::DoubleToCleanString(value);
	}

	va_end(valueList);

	std::cout << printOut << std::endl;
}

bool Mathematics::IsNaN(double value) {
	return value != value;
}

bool Mathematics::IsInfinite(double value) {
	return value == std::numeric_limits<double>::infinity();
}

bool Mathematics::IsFinite(double value) {
	return value != std::numeric_limits<double>::infinity();
}

int Mathematics::Sign(double value) {
		return (0 < value) - (value < 0);
}