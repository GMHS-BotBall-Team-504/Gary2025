#include "../include/positions.h"

shoulderPositions shoulderPos = {
    .starting = 1323,
    .parallelToGround = 640,
    .vertical = 1655,
    .ground = 722,
    .PVC = 900
};

elbowPositions elbowPos = {
    .starting = 918,
    .parallelToShoulder = 1400,
    .perpendicularToShoulder = 400,
    .ground = 1580,
    .PVC = 1500
};

wristPositions wristPos = {
    .starting = 120,
    .parallelToArm = 664,
    .perpendicularUpwards = 0,
    .perpedincularDownwards = 1776,
    .ground = 650,
    .PVC = 585
};

clawPositions clawPos = {
    .open = 78,
    .closedPoms = 1300,
    .closedPotato = 1078
};