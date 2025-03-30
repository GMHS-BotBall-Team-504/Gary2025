#include "../include/translation.h"
#include "../include/ports.h"
#include "../include/positions.h"
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


// Ran during the 1 minute before games start
void startUp() {
    alloff();
    disable_servos();
    msleep(500);
    servoPosition(servos.claw, clawPos.starting, 1);
    servoPosition(servos.elbow, elbowPos.starting, 1);
    servoPosition(servos.wrist, wristPos.starting, 1);
    for (int i = 0; i < 4; i++) {
        clear_motor_position_counter(i);
    }
    wait_for_light(analogPorts.underLight);
    shut_down_in(119);
}