#ifndef POSITIONS_H
#define POSITIONS_H

// Structure for shoulder variables
typedef struct {
    int starting;
    int parallelToGround;
    int vertical;
    int ground;
    int PVC;
    int strafe;
    int potato;
} shoulderPositions;

// Structure for elbow variables
typedef struct {
    int starting;
    int parallelToShoulder;
    int perpendicularToShoulder;
    int ground;
    int PVC;
    int strafe;
    int potato;
} elbowPositions;

// Structure for wrist variables
typedef struct {
    int starting;
    int parallelToArm;
    int perpendicularUpwards;
    int perpedincularDownwards;
    int ground;
    int PVC;
    int strafe;
    int potato;
} wristPositions;

// Structure for claw variables
typedef struct {
    int open;
    int closedPoms;
    int closedPotato;
    int closedBox;
} clawPositions;

// All values are in ticks; backLeft corner of the robot
typedef struct {
    float x;
    float y;
    float theta;
} RobotState;

// Declare the global variable for variables
extern shoulderPositions shoulderPos;
extern elbowPositions elbowPos;
extern wristPositions wristPos;
extern clawPositions clawPos;
extern RobotState robotState;

#endif // POSITIONS_H