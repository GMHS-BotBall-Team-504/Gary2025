#include "../include/positions.h"

elbowPositions elbowPos = {
    .starting = 0,
    .parallelToFloor = 1600,
    .vertical = 600,
    .ground = 0,
    .PVC = 0
};

wristPositions wristPos = {
    .starting = 0,
    .parallelToArm = 1200,
    .perpendicularUpwards = 200,
    .perpedincularDownwards = 2000,
    .ground = 0,
    .PVC = 0
};

clawPositions clawPos = {
    .starting = 0,
    .open = 78,
    .closedPoms = 1300,
    .closedPotato = 1078
};