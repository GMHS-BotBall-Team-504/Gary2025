#include <kipr/wombat.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../include/library.h"
#define startingDirection 180



int main() {
    
    enable_servos();

    // reset to downward position
    printf("Resetting servos...\n");
    runServoThreads((ServoParams[]) {
        {servos.shoulder, get_servo_position(servos.shoulder), shoulderPos.ground, 2},
        {servos.elbow, get_servo_position(servos.elbow), elbowPos.ground, 2},
        {servos.wrist, get_servo_position(servos.wrist), wristPos.ground, 2}
    }, 3);
    msleep(1500);
    closeClaw(0); // To close around poms size
    msleep(1500);
    set_servo_position(servos.elbow, 20);
    msleep(1000);
    set_servo_position(servos.wrist, wristPos.perpendicularUpwards);
    msleep(1000);

    return 0;
    // move the hinge upwards
    printf("Moving to first positions gradually...\n");
    runServoThreads((ServoParams[]) {
        {servos.shoulder, get_servo_position(servos.shoulder), 1300, 50},
        {servos.elbow, get_servo_position(servos.elbow), 720, 72}, // 218
        {servos.wrist, get_servo_position(servos.wrist), 1000, 72}
    }, 3);
    msleep(1500);
    openClaw();

    // // Example 2: Move three servos to the second set of positions gradually
    // printf("Moving to second positions gradually...\n");
    // runServoThreads((ServoParams[]) {
    //     {3, get_servo_position(3), 600, 2},
    //     {2, get_servo_position(2), sum - 600, 2},
    //     {1, get_servo_position(1), 2000, 5}
    // }, 3); 
    // msleep(600);
    // closeClaw(0); // To close around poms size

    disable_servos();
    return 0;
}