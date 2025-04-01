#include "../include/translation.h"
#include "../include/ports.h"
#include "../include/positions.h"
#include "../include/servos.h"
#include <kipr/wombat.h>
#include <pthread.h>
#include <stdlib.h>
#define constant 0.966

/* ----- Translational Movement ----- */

void forwardDrive(int units, int speed) {
    move_relative_position(wheels.frontLeft, speed, units);
    move_relative_position(wheels.backLeft, speed, units);
    move_relative_position(wheels.frontRight, constant * speed, constant * units);
    move_relative_position(wheels.backRight, constant * speed, constant * units);
    block_motor_done(0);
    msleep(10);
    stop(speed);
    return;
}

void backwardDrive(int units, int speed) {
    move_relative_position(wheels.frontLeft, -1 * speed, -1 * units);
    move_relative_position(wheels.backLeft, -1 * speed, -1 * units);
    move_relative_position(wheels.frontRight, -1 * constant * speed, -1 * constant * units);
    move_relative_position(wheels.backRight, -1 * constant * speed, -1 * constant * units);
    block_motor_done(0);
    msleep(10);
    stop(speed);
}

void rotate(int degrees, int speed) {
    move_relative_position(wheels.frontLeft, speed, degrees);
    move_relative_position(wheels.backLeft, speed, degrees);
    move_relative_position(wheels.frontRight, -1 * speed, -1 * degrees);
    move_relative_position(wheels.backRight, -1 * speed, -1 * degrees);
    for (int i = 0; i < 4; i++) {
        block_motor_done(i);
    }
    msleep(10);
    
}

// Revamped version of alloff so there's less drift
void stop(int motorSpeed) {
    for (int i = 0; i < 4; i++) {
        mav(i, (-1) * motorSpeed);
    }
    msleep(30);
    ao();
}

void centerDrive(int units, int speed) {
    
}

/* ----- Servo Movement ------- */

void servoPosition(int port, int position, int iterations) {
    enable_servo(port);
    float change = (float)(position - get_servo_position(port)) / iterations;
    for (int i = 0; i < iterations; i++) {
        set_servo_position(port, get_servo_position(port) + change);
        msleep(50);
    }
    while (get_servo_position(port) != position) {
        msleep(10);
    }
    disable_servo(port);

}

void openClaw() {
    enable_servo(servos.claw);
    set_servo_position(servos.claw, clawPos.open);
    msleep(500);
    disable_servo(servos.claw);
}

void closeClaw(int position) {
    enable_servo(servos.claw);
    if (position == 0) {
        set_servo_position(servos.claw, clawPos.closedPoms);
    }
    else {
        set_servo_position(servos.claw, clawPos.closedPotato);
    }
    msleep(500);
    disable_servo(servos.claw);
}

// We assume the robot is in the ground position
void verticalArm() {
    // turn on the necessary servos
    enable_servos();
    disable_servo(servos.claw);

    // enable the counterweight
    runServoThreads((ServoParams[]) {
        {servos.elbow, get_servo_position(servos.elbow), 200, 12},
        {servos.wrist, get_servo_position(servos.wrist), wristPos.perpendicularUpwards, 12}
    }, 2);

    // slowly move everything up
    runServoThreads((ServoParams[]) {
        {servos.shoulder, get_servo_position(servos.shoulder), shoulderPos.vertical, 30},
        {servos.elbow, get_servo_position(servos.elbow), 720, 45}, // 218
        {servos.wrist, get_servo_position(servos.wrist), 650, 45}
    }, 3);

    runServoThreads((ServoParams[]) {
        {servos.elbow, get_servo_position(servos.elbow), 1600, 10}, // 
        {servos.wrist, get_servo_position(servos.wrist), 710, 10}
    }, 2);
    msleep(200);
    printf("moved the arm up\n");
    return;
}


// Ran during the 1 minute before games start
void startUp() {
    alloff();
    disable_servos();
    msleep(500);

    for (int i = 0; i < 4; i++) {
        clear_motor_position_counter(i);
    }
    // wait_for_light(analogPorts.underLight);
    // shut_down_in(119);
    return;
}