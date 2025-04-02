#include "../include/library.h"
#include <math.h>


int main() {

    /* ---------- Pre-Run Tasks ---------- */
    startUp(); 

    /* ---------- Box Alignment ---------- */
    backwardDrive(1500, 1500);
    forwardDrive(77, 1500);

    /* ---------- Box Exit ---------- */
    rightDrive(3650, 1500);

    { // Open the claw and rotate to face the poms
        int motorParams[] = {2190, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.claw, clawPos.open, 2}
            }, 1
        };

        // Execute threads
        executeMovementandServoThreads(rotateThread, motorParams, &servoArgs);
    }

    /* ---------- Floor the Claw ---------- */
    runServoThreads((ServoParams[]) {
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2}
    }, 2); // Set up so the robot doesn't break itself when it moves the servos
    
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

    /* ---------- START POM SET 1 ---------- */
    
    centerDrive(2800, 1500, 0.2);
    rotate(200, 1500);
    closeClaw(0);
    msleep(300);

    { // Turn to face the first box
        int motorParams[] = {580, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.elbow, elbowPos.PVC, 5},
                {servos.wrist, wristPos.PVC, 5}
            }, 2
        };

        // Execute threads
        executeMovementandServoThreads(rotateThread, motorParams, &servoArgs);
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