#include "../include/library.h"

int main() {
    startUp();
    enable_servos();

    /* ------------ BASIC LIFTING CODE ------------------ */
    // reset to downward position
    printf("Resetting servos...\n");
    runServoThreads((ServoParams[]) {
        {servos.shoulder, get_servo_position(servos.shoulder), shoulderPos.ground, 2},
        {servos.elbow, get_servo_position(servos.elbow), elbowPos.ground, 2},
        {servos.wrist, get_servo_position(servos.wrist), wristPos.ground, 2}
    }, 3);
    msleep(1500);
    closeClaw(0); // To close around poms size
    msleep(500);

    runServoThreads((ServoParams[]) {
        {servos.shoulder, get_servo_position(servos.shoulder), shoulderPos.PVC, 2},
        {servos.elbow, get_servo_position(servos.elbow), elbowPos.PVC, 2},
        {servos.wrist, get_servo_position(servos.wrist), wristPos.PVC, 2}
    }, 3);
    msleep(500);
    openClaw();
    msleep(500);


    /* ------------- MOVEMENT AND SERVO CODE -------------- */
    int motorParams[] = {3000, 1500};
    ServoThreadArgs servoArgs = {
        (ServoParams[]) {
            {servos.elbow, get_servo_position(servos.elbow), elbowPos.perpendicularToShoulder, 10},
            {servos.wrist, get_servo_position(servos.wrist), wristPos.perpendicularUpwards, 10}
        },
        2
    };

    // Execute threads
    executeMovementandServoThreads(motorParams, &servoArgs);

    // Clean up
    disable_servos();
    printf("All threads finished.\n");


    disable_servos();
    return 0;
}