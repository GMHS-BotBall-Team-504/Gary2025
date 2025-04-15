#include "../include/positions.h"

/*  */
shoulderPositions shoulderPos = {
    .starting = 1950,
    .parallelToGround = 600,
    .vertical = 1700,
    .ground = 1350,
    .PVC = 1474,
    .strafe = 1900,
    .potato = 1350
};

/* Pre-Set Positions on the Elbow Hinge*/
elbowPositions elbowPos = {
    .starting = 0,
    .parallelToShoulder = 27,
    .perpendicularToShoulder = 1115,
    .ground = 2047,
    .PVC = 1340,
    .strafe = 1000,
    .potato = 1950
};

/*  */
wristPositions wristPos = {
    .starting = 0,
    .parallelToArm = 664,
    .perpendicularUpwards = 0,
    .perpedincularDownwards = 1776,
    .ground = 390,
    .PVC = 638, 
    .strafe = 250,
    .potato = 200
};

/*  */
clawPositions clawPos = {
    .open = 500,
    .closedPoms = 1750,
    .closedPotato = 1650,
    .closedBox = 944
}; 

RobotState robotState = {
    .x = 0.0,
    .y = 0.0,
    .theta = 0.0
};