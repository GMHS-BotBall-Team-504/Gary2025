#include "../include/ports.h"

// Initialize the wheel ports with corresponding port numbers
WheelPorts wheels = {
    .frontLeft = 3,    // Port 3
    .frontRight = 0,   // Port 0
    .backLeft = 2,     // Port 2
    .backRight = 1     // Port 1
};

servoPorts servos = {
    .shoulder = 0,
    .elbow = 1,
    .wrist = 2, 
    .claw = 3
};

AnalogPorts analogPorts = {
    .underLight = 0,
    .leftRange = 2,
    .rightRange = 3
};

DigitalPorts digitalPorts = {
    
};