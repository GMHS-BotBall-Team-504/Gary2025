#include "../include/ports.h"

// Initialize the wheel ports with corresponding port numbers
WheelPorts wheels = {
    .frontLeft = 1,    // Port 1
    .frontRight = 0,   // Port 0
    .backLeft = 3,     // Port 3
    .backRight = 2     // Port 2
};

servoPorts servos = {
    .elbow = 1,   // Port 1
    .wrist = 0, 
    .claw = 2
};

AnalogPorts analogPorts = {
    .underLight = 1,
    
};

DigitalPorts digitalPorts = {
    .frontLeftButton = 0,
    .frontRightButton = 1,
    .backLeftButton = 2, 
    .backRightButton = 3, 
};