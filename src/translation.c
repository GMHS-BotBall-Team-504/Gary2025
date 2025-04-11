#include "../include/translation.h"
#include "../include/ports.h"
#include "../include/positions.h"
#include "../include/servos.h"
#include <kipr/wombat.h>
#include <pthread.h>
#include <stdlib.h>
#define constant 0.966

/* ----- Translational Movement ----- */

/// @brief Moves the robot forward
/// @param units Target ticks traveled
/// @param speed Speed in ticks/s
/// @details The robot will move forward at the given speed for the given number of ticks
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
    backStop(speed);
}

void rightDrive(int units, int speed) {
    move_relative_position(wheels.frontLeft, -1 * speed, -1 * units);
    move_relative_position(wheels.backLeft, 1 * speed, 1 * units);
    move_relative_position(wheels.frontRight, 1 * speed, 1 * units);
    move_relative_position(wheels.backRight, -1 * speed, -1 * units);
    block_motor_done(0);
    msleep(10);
    ao();
}

/*! \brief Translates the robot in any direction;
 *         360 degrees;
 *         Cannot rotate
 *
 *  blah blah blah
 * 
 * @param distance Target cm traveled
 * @param radians Angle in radians to turn
 * @param speed Speed in cm/s
 */
void angleDrive(int distance, int degrees, int speed) {
    // Converting degrees into radians
    float radians = degrees * M_PI / 180;

    // Calculate motor speeds based on direction
    int topRight = sin(radians - M_PI/4) * speed;
    int topLeft = sin(radians + M_PI/4) * speed;

    move_relative_position(wheels.frontLeft, topLeft, distance);
    move_relative_position(wheels.backLeft, topRight, distance);
    move_relative_position(wheels.frontRight, topRight, distance);
    move_relative_position(wheels.backRight, topLeft, distance);

    for (int i = 0; i < 4; i++) {
        block_motor_done(i);
    }
    msleep(10);
    return;
}

/// @brief
void rotationalDrive(int distance, int directionsRadians, int turningRadians, int rotationalSpeed, int translationalSpeed) {

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

void backStop(int motorSpeed) {
    for (int i = 0; i < 4; i++) {
        mav(i, motorSpeed);
    }
    msleep(30);
    ao();
}

void rotateStop(int motorSpeed) {
    mav(wheels.backLeft, motorSpeed);
    mav(wheels.frontLeft, motorSpeed);
    mav(wheels.backRight, (-1) * motorSpeed);
    mav(wheels.frontRight, (-1) * motorSpeed);
    msleep(30);
    ao();
}

void centerDrive(int targetDistance, int baseSpeed, int kp) {
    int leftDistance, rightDistance, error, correction;
    int traveledDistance = 0;

    // Reset motor position counters
    for (int i = 0; i < 4; i++) {
        clear_motor_position_counter(i);
    }

    while (traveledDistance < targetDistance) {
        // Read rangefinder values
        leftDistance = analog(analogPorts.leftRange);
        rightDistance = analog(analogPorts.rightRange);

        // Calculate error and correction
        error = leftDistance - rightDistance;
        correction = kp * error;

        // Adjust motor speeds
        int leftSpeed = baseSpeed - correction;
        int rightSpeed = baseSpeed + correction;

        // Move the robot forward
        mav(wheels.frontLeft, leftSpeed);
        mav(wheels.backLeft, leftSpeed);
        mav(wheels.frontRight, rightSpeed);
        mav(wheels.backRight, rightSpeed);

        // Update traveled distance (assuming frontLeft motor is representative)
        traveledDistance = get_motor_position_counter(wheels.frontLeft);

        msleep(20); // Small delay for stability
    }

    // Stop the robot
    ao();
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
    printf("opened claw\n");
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
        {servos.elbow, 200, 12},
        {servos.wrist, wristPos.perpendicularUpwards, 12}
    }, 2);
    disable_servo(servos.claw);
    // slowly move everything up
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.vertical, 30},
        {servos.elbow, 720, 45}, // 218
        {servos.wrist, 650, 45}
    }, 3);
    disable_servo(servos.claw);
    runServoThreads((ServoParams[]) {
        {servos.elbow, 1600, 10}, // 
        {servos.wrist, 710, 10}
    }, 2);
    msleep(200);
    closeClaw(0);
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
    verticalArm();
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.starting, 10},
        {servos.elbow, elbowPos.starting, 10},
        {servos.wrist, wristPos.starting, 10}
    }, 3);
    msleep(2000);
    return;
}