#include "../include/library.h"

int main() {
    startUp();
    openClaw();
    /* ------------ BASIC LIFTING CODE ------------------ */
    // reset to downward position
    // printf("Resetting servos...\n");
    // runServoThreads((ServoParams[]) {
    //     {servos.shoulder, get_servo_position(servos.shoulder), shoulderPos.ground, 2},
    //     {servos.elbow, get_servo_position(servos.elbow), elbowPos.ground, 2},
    //     {servos.wrist, get_servo_position(servos.wrist), wristPos.ground, 2}
    // }, 3);
    // msleep(500);
    // closeClaw(0); // To close around poms size
    // // msleep(500);
    // // runServoThreads((ServoParams[]) {
    // //     {servos.shoulder, get_servo_position(servos.shoulder), shoulderPos.PVC, 2},
    // //     {servos.elbow, get_servo_position(servos.elbow), elbowPos.PVC, 2},
    // //     {servos.wrist, get_servo_position(servos.wrist), wristPos.PVC, 2}
    // // }, 3);
    // // msleep(500);
    // verticalArm();
    // openClaw();
    // msleep(500);


    // /* ------------- MOVEMENT AND SERVO CODE -------------- */

    runServoThreads((ServoParams[]) {
        {servos.shoulder, get_servo_position(servos.shoulder), shoulderPos.ground, 2},
        {servos.elbow, get_servo_position(servos.elbow), elbowPos.ground, 2},
        {servos.wrist, get_servo_position(servos.wrist), wristPos.ground, 2}
    }, 3);

    {
        int motorParams[] = {1500, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
            }, 0
        };

        // Execute threads
        executeMovementandServoThreads(motorParams, &servoArgs);
    }
    closeClaw(0); // To close around poms size
    msleep(20);
    {
        int motorParams[] = {500, 1500};
        ServoThreadArgs servoArgs = {
            (ServoParams[]) {
                {servos.elbow, get_servo_position(servos.elbow), elbowPos.PVC, 20},
                {servos.wrist, get_servo_position(servos.wrist), wristPos.PVC, 20}
            }, 2
        };

        // Execute threads
        executeMovementandServoThreads(motorParams, &servoArgs);
    }
    msleep(50);
    openClaw();

    // Clean up
    disable_servos();
    printf("All threads finished.\n");

    return 0;
}

    // int motorParams[] = {500, 1500};
    // ServoThreadArgs servoArgs = {
    //     (ServoParams[]) {
    //         {servos.elbow, get_servo_position(servos.elbow), elbowPos.perpendicularToShoulder, 10},
    //         {servos.wrist, get_servo_position(servos.wrist), wristPos.perpendicularUpwards, 10}
    //     }, 2
    // };