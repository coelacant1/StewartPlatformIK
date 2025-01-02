# Stewart Platform Inverse Kinematics for C++

This repository contains a C++ application for Windows that calculates the inverse kinematics (IK) for a Stewart Platform. The application takes six geometrical parameters for the platform as command-line arguments, then waits for position and orientation inputs (`x`, `y`, `z`, `yaw`, `pitch`, `roll`) to calculate the required actuator lengths.

## Overview

A **Stewart Platform** (also known as a **hexapod**) is a parallel robotic mechanism with six independent actuators. By adjusting these actuator lengths, the top plate (platform) can be moved and oriented in 3D space.

This application performs the following:
- Reads in six configuration parameters for the platform:
  - basePlateRadius (br)
  - baseMountingAngle (bm)
  - platformPlateRadius (pr)
  - platformMountingAngle (pm)
  - baseHeight (bh)
  - maximumLength (ml)
- Constructs a `StewartPlatform` object with these parameters.
- Continuously reads user inputs for the desired platform position and rotation:
  - `x`, `y`, `z`
  - `yaw` (`ya`), `pitch` (`pi`), `roll` (`ro`)
- Returns the computed actuator lengths (`ActuatorLengths`) for each new position and orientation.

## Installation and Building

1. **Clone the Repository**  
   Download or clone this repository to your local machine.

2. **Open/Configure a C++ Development Environment on Windows**  
   - You can use Microsoft Visual Studio, or any other C++17-compliant compiler.
   - Ensure that CMake or your chosen build system is configured for your environment if needed.

3. **Compile the Code**  
   - Add the `StewartPlatform.cpp` and `StewartPlatform.h` source files, as well as `main.cpp`, to your project.
   - Build the project in Release or Debug mode.

## Usage

Once the executable is built, run it from the command line with the six required arguments:

Example:
```bash
StewartPlatform.exe 500 10 500 10 930 450
```

Where the arguments represent:
- `500` -> basePlateRadius (br)
- `10` -> baseMountingAngle (bm)
- `500` -> platformPlateRadius (pr)
- `10` -> platformMountingAngle (pm)
- `930` -> baseHeight (bh)
- `450` -> maximumLength (ml)

After starting the application, you can enter lines containing six values:
```bash
x y z yaw pitch roll
```

For instance:
```bash
0 0 0 0 0 0 10 5 20 0.5 0.2 1.0 ...
```

## Contributing

Feel free to submit pull requests or create issues if you have suggestions for improvements. All contributions (bug reports, enhancement ideas, PRs) are welcome.

## License

This project is provided as-is with no specific license. If you wish to use or modify the code, please include appropriate credit.
