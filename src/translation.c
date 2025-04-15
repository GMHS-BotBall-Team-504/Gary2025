#include "../include/translation.h"
#include "../include/ports.h"
#include "../include/positions.h"
#include "../include/servos.h"
#include <kipr/wombat.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#define constant 1
#define TAPE_THRESHOLD 1500

/* ----- Translational Movement ----- */

/*! @brief Drives the robot in a direction based on the given angle and speed
 * @param angle Angle in degrees
 * @param speed Translational speed
 * @param omega Angular velocity (rotation speed)
 * @param maxSpeed Maximum speed for the wheels
 * @details The robot will move in the direction specified by the angle, with the given translational speed and angular velocity.
 */
void angularDrive(float angle, float speed, float omega, int maxSpeed) {
    // Calculate vx and vy based on the angle and speed
    float vx = speed * cos(angle); // X-component of velocity
    float vy = speed * sin(angle); // Y-component of velocity

    // Calculate the speeds for each wheel
    int frontLeftSpeed = (int)(vx + vy + omega);
    int backLeftSpeed = (int)(vx - vy + omega);
    int frontRightSpeed = (int)(vx - vy - omega);
    int backRightSpeed = (int)(vx + vy - omega);

    // Normalize speeds to ensure they don't exceed maxSpeed
    int maxWheelSpeed = fmax(fmax(abs(frontLeftSpeed), abs(frontRightSpeed)),
                             fmax(abs(backLeftSpeed), abs(backRightSpeed)));
    if (maxWheelSpeed > maxSpeed) {
        frontLeftSpeed = frontLeftSpeed * maxSpeed / maxWheelSpeed;
        frontRightSpeed = frontRightSpeed * maxSpeed / maxWheelSpeed;
        backLeftSpeed = backLeftSpeed * maxSpeed / maxWheelSpeed;
        backRightSpeed = backRightSpeed * maxSpeed / maxWheelSpeed;
    }

    // Set motor speeds
    mav(wheels.frontLeft, frontLeftSpeed);
    mav(wheels.frontRight, frontRightSpeed);
    mav(wheels.backLeft, backLeftSpeed);
    mav(wheels.backRight, backRightSpeed);
}


void crash(int backLeft, int backRight, int frontLeft, int frontRight) {
    mav(wheels.backLeft, (-1) * backLeft);
    mav(wheels.backRight, (-1) * backRight);
    mav(wheels.frontLeft, (-1) * frontLeft);
    mav(wheels.frontRight, (-1) * frontRight);
    msleep(30);
    ao();

}

/*! @brief Aligns the robot to the tape
 * @param direction Direction to align (1 for left, -1 for right)
 * @param ticksPerSecond Speed in ticksDegrees/sec
 * @details The robot will move towards the tape until it detects it.
 */
void alignRotation(int direction, int ticksPerSecond) {
    int speed = (direction == 1) ? -1 * ticksPerSecond : ticksPerSecond;
    move_at_velocity(wheels.frontLeft, speed);
    move_at_velocity(wheels.backLeft, speed);
    move_at_velocity(wheels.frontRight, (-1) * speed);
    move_at_velocity(wheels.backRight, (-1) * speed);
    while (analog(analogPorts.frontLight) < TAPE_THRESHOLD) {
        msleep(10);
    }
    crash(speed, (-1) * speed, speed, (-1) * speed);
    printf("Hit rotational tape\n");
}

/*! @brief Aligns the robot to the tape
 * @param ticksPerSecond Speed in ticksDegrees/sec
 * @details The robot will move towards the tape until it detects it.
*/
void alignBack(int ticksPerSecond) {
    mav(wheels.frontLeft, -ticksPerSecond);
    mav(wheels.backLeft, -ticksPerSecond);
    mav(wheels.frontRight, -ticksPerSecond);
    mav(wheels.backRight, -ticksPerSecond);
    while (analog(analogPorts.underLight) < TAPE_THRESHOLD) {
        msleep(5);
    }
    crash(-ticksPerSecond, -ticksPerSecond , -ticksPerSecond, -ticksPerSecond);
    printf("Hit back tape\n");
    return;
}

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

    move_relative_position(wheels.frontLeft, 1 * speed, 1 * units);
    move_relative_position(wheels.backLeft, -1 * speed, -1 * units);
    move_relative_position(wheels.frontRight, -1 * speed, -1 * units);
    move_relative_position(wheels.backRight, 1 * speed, 1 * units);
    msleep(30);
    ao();
}

void leftDrive(int units, int speed) {
    move_relative_position(wheels.frontLeft, 1 * speed, 1 * units);
    move_relative_position(wheels.backLeft, -1 * speed, -1 * units);
    move_relative_position(wheels.frontRight, -1 * speed, -1 * units);
    move_relative_position(wheels.backRight, 1 * speed, 1 * units);
    block_motor_done(0);
    msleep(10);
    
    move_relative_position(wheels.frontLeft, -1 * speed, -1 * units);
    move_relative_position(wheels.backLeft, 1 * speed, 1 * units);
    move_relative_position(wheels.frontRight, 1 * speed, 1 * units);
    move_relative_position(wheels.backRight, -1 * speed, -1 * units);
    msleep(30);
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
    move_relative_position(wheels.frontRight, (-1) * speed, (-1) * degrees);
    move_relative_position(wheels.backRight, (-1) * speed, (-1) * degrees);
    for (int i = 0; i < 4; i++) {
        block_motor_done(i);
    }
    msleep(10);
    
    move_relative_position(wheels.frontLeft, (-1) * speed, (-1) * degrees);
    move_relative_position(wheels.backLeft, (-1) * speed, (-1) * degrees);
    move_relative_position(wheels.frontRight, speed, degrees);
    move_relative_position(wheels.backRight, speed, degrees);
    msleep(30);
    ao();
    return;
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

void strafePosition() {
    enable_servos();
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.strafe, 2},
        {servos.elbow, elbowPos.strafe, 2},
        {servos.wrist, wristPos.strafe, 2}
    }, 3);
    msleep(200);
    disable_servos();
}

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