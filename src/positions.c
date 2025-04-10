#include "../include/positions.h"

/*  */
shoulderPositions shoulderPos = {
    .starting = 1800,
    .parallelToGround = 600,
    .vertical = 1700,
    .ground = 629,
    .PVC = 934
};

/* Pre-Set Positions on the Elbow Hinge*/
elbowPositions elbowPos = {
    .starting = 500,
    .parallelToShoulder = 27,
    .perpendicularToShoulder = 1115,
    .ground = 1452,
    .PVC = 1080
};

/*  */
wristPositions wristPos = {
    .starting = 0,
    .parallelToArm = 664,
    .perpendicularUpwards = 0,
    .perpedincularDownwards = 1776,
    .ground = 179,
    .PVC = 547
};

/*  */
clawPositions clawPos = {
    .open = 100,
    .closedPoms = 1500,
    .closedPotato = 1200
};