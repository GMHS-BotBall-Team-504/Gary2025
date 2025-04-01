#include "../include/library.h"
#include <math.h>

/// @brief Translates the robot in any direction; 360 degrees; Cannot rotate
/// @param distance Target cm traveled
/// @param radians Angle in radians to turn
/// @param speed Speed in cm/s
void angleDrive(int distance, int degrees, int speed) {
    // Converting degrees into radians
    float radians = degrees * M_PI / 180;

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

void rotationalDrive(int distance, int directionsRadians, int turningRadians, int rotationalSpeed, int translationalSpeed) {

}


int main() {

    startUp();
    msleep(2500);
    enable_servo(servos.claw);
    set_servo_position(servos.claw, clawPos.open);
    msleep(500);
    disable_servo(servos.claw);
    backwardDrive(1500, 1500);
    forwardDrive(77, 1500);
    rightDrive(3650, 1500);
    rotate(2190, 1500);
    enable_servo(servos.claw);
    set_servo_position(servos.claw, clawPos.open);
    msleep(500);
    disable_servo(servos.claw);
    msleep(50);
    runServoThreads((ServoParams[]) {
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2}
    }, 2);
    
    {
        int motorParams[] = {1270, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.shoulder, shoulderPos.ground, 2},
                {servos.elbow, elbowPos.ground, 2},
            {servos.wrist, wristPos.ground, 2}
            }, 3
        };

        // Execute threads
        executeMovementandServoThreads(backwardDriveThread, motorParams, &servoArgs);
    }
    /* ------------ START POM SET 1 ------------------ */
    
    forwardDrive(2770, 1500);
    rotate(200, 1500);
    closeClaw(0);
    msleep(300);

    {
        int motorParams[] = {580, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.elbow, elbowPos.PVC, 5},
                {servos.wrist, wristPos.PVC, 5}
            }, 2
        };

        // Execute threads
        executeMovementandServoThreads(rotateThread ,motorParams, &servoArgs);
    }

    forwardDrive(950, 1500);
    msleep(1200);
    enable_servo(servos.claw);
    set_servo_position(servos.claw, clawPos.open);
    msleep(500);
    disable_servo(servos.claw);
    msleep(50);
    disable_servos();

    /* ------------- END POM SET 1 ---------------- */

    return 0;

    startUp();
    backwardDrive(1500, 1500);
    return 0;
    openClaw();
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.PVC, 2},
        {servos.elbow, elbowPos.PVC, 2},
        {servos.wrist, wristPos.PVC, 2}
    }, 3);

    /* ------------------------ START POM SET 2 ------------------------ */
    forwardDrive(450, 1500);
    
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.ground, 2},
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2}
    }, 3);
    rotate(200, 1500);
    forwardDrive(200, 1500);
    rotate(200, 1500);
    closeClaw(0);

    return 0;



    /* ------------ START POM SET 1 ------------------ */
    // reset to downward position
    printf("Resetting servos...\n");
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.ground, 2},
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2}
    }, 3);
    msleep(300);
    forwardDrive(3000, 1500);
    rotate(200, 1500);
    closeClaw(0);

    {
        int motorParams[] = {700, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.elbow, elbowPos.PVC, 5},
                {servos.wrist, wristPos.PVC, 5}
            }, 2
        };

        // Execute threads
        executeMovementandServoThreads(rotateThread ,motorParams, &servoArgs);
    }

    forwardDrive(700, 1500);
    openClaw();

    /* ------------- END POM SET 1 ---------------- */
    
    msleep(500);
    closeClaw(0); // To close around poms size
    msleep(500);
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.PVC, 2},
        {servos.elbow, elbowPos.PVC, 2},
        {servos.wrist, wristPos.PVC, 2}
    }, 3);
    msleep(500);
    verticalArm();
    openClaw();
    msleep(500);


    // /* ------------- MOVEMENT AND SERVO CODE -------------- */

    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.ground, 2},
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2}
    }, 3);

    {
        int motorParams[] = {4500, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
            }, 0
        };

        // Execute threads
        executeMovementandServoThreads(forwardDriveThread, motorParams, &servoArgs);
    }

    closeClaw(0); // To close around poms size
    msleep(20);
    
    {
        int motorParams[] = {3000, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.elbow, elbowPos.PVC, 20},
                {servos.wrist, wristPos.PVC, 20}
            }, 2
        };

        // Execute threads
        executeMovementandServoThreads(backwardDriveThread ,motorParams, &servoArgs);
    }


    msleep(50);
    openClaw();
    
    verticalArm();

    // Clean up
    disable_servos();
    printf("All threads finished.\n");

    return 0;
}

    // int motorParams[] = {500, 1500};
    // ServoThreadArgs servoArgs = {
    //     (ServoParams[]) {
    //         {servos.elbow, elbowPos.perpendicularToShoulder, 10},
    //         {servos.wrist, wristPos.perpendicularUpwards, 10}
    //     }, 2
    // };