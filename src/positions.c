#include "../include/positions.h"

/*  */
shoulderPositions shoulderPos = {
    .starting = 1950,
    .parallelToGround = 600,
    .vertical = 1700,
    .ground = 1474,
    .PVC = 1300,
    .strafe = 1900
};

/* Pre-Set Positions on the Elbow Hinge*/
elbowPositions elbowPos = {
    .starting = 0,
    .parallelToShoulder = 27,
    .perpendicularToShoulder = 1115,
    .ground = 2047,
    .PVC = 160,
    .strafe = 1000
};

/*  */
wristPositions wristPos = {
    .starting = 0,
    .parallelToArm = 664,
    .perpendicularUpwards = 0,
    .perpedincularDownwards = 1776,
    .ground = 126,
    .PVC = 638, 
    .strafe = 250
};

/*  */
clawPositions clawPos = {
    .open = 500,
    .closedPoms = 1750,
    .closedPotato = 1500
}; 