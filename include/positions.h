#ifndef POSITIONS_H
#define POSITIONS_H

// Structure for elbow variables
typedef struct {
    int starting;
    int parallelToFloor;
    int vertical;
    int ground;
    int PVC;
} elbowPositions;

// Structure for wrist variables
typedef struct {
    int starting;
    int parallelToArm;
    int perpendicularUpwards;
    int perpedincularDownwards;
    int ground;
    int PVC;
} wristPositions;

// Structure for claw variables
typedef struct {
    int open;
    int closedPoms;
    int closedPotato;
} clawPositions;

// Declare the global variable for variables
extern elbowPositions elbowPos;
extern wristPositions wristPos;
extern clawPositions clawPos;

#endif // POSITIONS_H