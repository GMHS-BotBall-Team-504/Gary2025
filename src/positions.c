#include "../include/positions.h"

shoulderPositions shoulderPos = {
    .starting = 1800,
    .parallelToGround = 640,
    .vertical = 1655,
    .ground = 629,
    .PVC = 934
};

elbowPositions elbowPos = {
    .starting = 500,
    .parallelToShoulder = 1400,
    .perpendicularToShoulder = 400,
    .ground = 1452,
    .PVC = 968
};

wristPositions wristPos = {
    .starting = 0,
    .parallelToArm = 664,
    .perpendicularUpwards = 0,
    .perpedincularDownwards = 1776,
    .ground = 589,
    .PVC = 898
};

clawPositions clawPos = {
    .open = 200,
    .closedPoms = 1600,
    .closedPotato = 1300
};