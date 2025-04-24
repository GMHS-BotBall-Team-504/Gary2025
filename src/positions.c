#include "../include/positions.h"

/*  */
shoulderPositions shoulderPos = {
    .starting = 1950,
    .parallelToGround = 600,
    .vertical = 1700,
    .ground = 1460,
    .PVC = 1474,
    .strafe = 1730,
    .potato = 1350,
    .drop = 1756
};

/* Pre-Set Positions on the Elbow Hinge*/
elbowPositions elbowPos = {
    .starting = 0,
    .parallelToShoulder = 27,
    .perpendicularToShoulder = 1115,
    .ground = 1870,
    .PVC = 1400,
    .strafe = 360,
    .potato = 1818,
    .drop = 308
};

/*  */
wristPositions wristPos = {
    .starting = 0,
    .parallelToArm = 664,
    .perpendicularUpwards = 0,
    .perpedincularDownwards = 1776,
    .ground = 300,
    .PVC = 600,
    .strafe = 250,
    .potato = 463,
    .drop = 1838
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