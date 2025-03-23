#ifndef VARIABLES_H
#define VARIABLES_H

// Structure for wheel ports
typedef struct {
    int frontLeft;   // Corresponds to port 1
    int frontRight;  // Corresponds to port 0
    int backLeft;    // Corresponds to port 3
    int backRight;   // Corresponds to port 2
} WheelPorts;

// Declare the global variable for wheel ports
extern WheelPorts wheels;
extern ;

#endif // VARIABLES_H