#include "../include/library.h"
#include <math.h>


int main() {

    /*
    startUp();

    {
        int motorParams[] = {1570, 1500};
        ServoThreadArgs ll = {
            (ServoParams[]) {
                {servos.claw, clawPos.open, 1},
                {servos.elbow, elbowPos.starting, 1},
                {servos.shoulder, shoulderPos.ground, 1},
            }, 3
        };

        executeMovementandServoThreads(forwardDriveThread, motorParams, &ll);
    };

        return 0;

    */

    /* ---------- Pre-Run Tasks ---------- */
    startUp();


    /* ---------- Box Alignment ---------- */
    backwardDrive(1300, 1500);
    forwardDrive(350, 1500);

    /* ---------- Box Exit ---------- */
    rightDrive(3650, 1500);

    { // Open the claw and rotate to face the poms
        int motorParams[] = {1570, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.claw, clawPos.open, 2}
            }, 1
        };

        // Execute threads
        executeMovementandServoThreads(rotateThread, motorParams, &servoArgs);
    }
    mav(wheels.frontLeft, 200);
    mav(wheels.backLeft, 200);
    mav(wheels.frontRight, -200);
    mav(wheels.backRight, -200);
    while (analog(5) < 1500) {
        msleep(10);
    }
    ao();
    rotate(220, 1500);
    backwardDrive(300, 1500);
    /* ---------- Floor the Claw ---------- */
    runServoThreads((ServoParams[]) {
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2}
    }, 2); // Set up so the robot doesn't break itself when it moves the servos
    
    { // Floor the overall extension while also backing up to position the poms
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
    
    // Collect the poms
    centerDrive(3150, 1500, 0.48);
    rotate(200, 1500);
    closeClaw(0);
    msleep(100);
    forwardDrive(400, 1500);

    { // Turn to face the first box
        int motorParams[] = {600, 1200};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.elbow, elbowPos.PVC, 2},
                {servos.wrist, wristPos.PVC, 2}
            }, 2
        };

        // Execute threads
        executeMovementandServoThreads(rotateThread, motorParams, &servoArgs);
    }
    forwardDrive(950, 1500);
    rightDrive(-20, -1500);
    msleep(200);
    openClaw();
    msleep(50);
    disable_servos();

    /* ------------- Set up POM SET 2 ---------------- */

    backwardDrive(1600, 1500);
    rotate(-870, -1500);
    {
     // Turn to face the first box
     int motorParams[] = {-300, -1500};
     ServoThreadArgs servoArgs = {
         (ServoParams[]) {
            {servos.shoulder, shoulderPos.ground, 2},
            {servos.elbow, elbowPos.ground, 2},
            {servos.wrist, wristPos.ground, 2}
         }, 3
     };

     // Execute threads
     executeMovementandServoThreads(rightDriveThread, motorParams, &servoArgs);
    }
    rightDrive(-300, -1500);
    forwardDrive(500, 1500);
    
    return 0;

    /* ------------------------ START POM SET 2 ------------------------ */
    
    angleDrive(-200, 0, 1500);
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