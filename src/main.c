#include "../include/library.h"

int main() {
    startUp();
    closeClaw(0);

    /* ------------ BASIC LIFTING CODE ------------------ */
    // reset to downward position
    printf("Resetting servos...\n");
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.ground, 2},
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2}
    }, 3);
    // msleep(500);
    // closeClaw(0); // To close around poms size
    // // msleep(500);
    // // runServoThreads((ServoParams[]) {
    // //     {servos.shoulder, shoulderPos.PVC, 2},
    // //     {servos.elbow, elbowPos.PVC, 2},
    // //     {servos.wrist, wristPos.PVC, 2}
    // // }, 3);
    // // msleep(500);
    // verticalArm();
    // openClaw();
    // msleep(500);


    // /* ------------- MOVEMENT AND SERVO CODE -------------- */

    // runServoThreads((ServoParams[]) {
    //     {servos.shoulder, shoulderPos.ground, 2},
    //     {servos.elbow, elbowPos.ground, 2},
    //     {servos.wrist, wristPos.ground, 2}
    // }, 3);

    // {
    //     int motorParams[] = {1500, 1500};
    //     ServoThreadArgs servoArgs = {
    //         (ServoParams[]) {
    //         }, 0
    //     };

    //     // Execute threads
    //     executeMovementandServoThreads(forwardDriveThread, motorParams, &servoArgs);
    // }

    // closeClaw(0); // To close around poms size
    // msleep(20);
    
    // {
    //     int motorParams[] = {1500, 1500};
    //     ServoThreadArgs servoArgs = {
    //         (ServoParams[]) {
    //             {servos.elbow, elbowPos.PVC, 20},
    //             {servos.wrist, wristPos.PVC, 20}
    //         }, 2
    //     };

    //     // Execute threads
    //     executeMovementandServoThreads(backwardDriveThread ,motorParams, &servoArgs);
    // }

    // msleep(50);
    // openClaw();
    
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