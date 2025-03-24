#include "../include/ports.h"

// Initialize the wheel ports with corresponding port numbers
WheelPorts wheels = {
    .frontLeft = 1,    // Port 1
    .frontRight = 0,   // Port 0
    .backLeft = 3,     // Port 3
    .backRight = 2     // Port 2
};

servoPorts servos = {
    .elbowHinge = 1,   // Port 1
    .wrist = 0, 
    .claw = 2
};

analogPorts analog = {
    .underLight = 1,
    
};

digitalPorts digital = {
    .frontLeftButton = 0,
    .frontRightButton = 1,
    .backLeftButton = 2, 
    .backRightButton = 3, 
};