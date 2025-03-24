#ifndef VARIABLES_H
#define VARIABLES_H

// Structure for wheel ports
typedef struct {
    int frontLeft;   // Corresponds to port 1
    int frontRight;  // Corresponds to port 0
    int backLeft;    // Corresponds to port 3
    int backRight;   // Corresponds to port 2
} WheelPorts;

// Structure for servo ports
typedef struct {
    int elbowHinge;   // Corresponds to port 1
    int wrist;  // Corresponds to port 0
    int claw;    // Corresponds to port 3
} servoPorts;

// Structure for analog ports (range)
typedef struct {
    int underLight;
} analogPorts;

// Structure for digital ports (0, 1)
typedef struct {
    int frontLeftButton;
    int frontRightButton;
    int backLeftButton;
    int backRightButton;
} digitalPorts;


// Declare the global variable for ports
extern WheelPorts wheels;
extern servoPorts servos;
extern analogPorts analog;
extern digitalPorts digital;

#endif // VARIABLES_H