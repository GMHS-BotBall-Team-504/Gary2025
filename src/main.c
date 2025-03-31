#include <kipr/wombat.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../include/library.h"

// Wrapper function for forwardDrive
void* forwardDriveThread(void* arg) {
    int* params = (int*) arg; // Cast the argument to an int array
    int units = params[0];   // Extract the units
    int speed = params[1];   // Extract the speed
    printf("Starting forward drive: units=%d, speed=%d\n", units, speed);
    forwardDrive(units, speed); // Call the forwardDrive function
    printf("Forward drive complete.\n");
    return NULL;
}

typedef struct {
    ServoParams* params; // Pointer to the array of ServoParams
    int count;           // Number of servos to move
} ServoThreadArgs;

int main() {
    
    enable_servos();


    // reset to downward position
    printf("Resetting servos...\n");
    runServoThreads((ServoParams[]) {
        {servos.shoulder, get_servo_position(servos.shoulder), shoulderPos.ground, 2},
        {servos.elbow, get_servo_position(servos.elbow), elbowPos.ground, 2},
        {servos.wrist, get_servo_position(servos.wrist), wristPos.ground, 2}
    }, 3);
    msleep(1500);
    closeClaw(0); // To close around poms size
    msleep(1500);

    verticalArm();
    msleep(500);

    // // Create the threads
    // pthread_t motorThread, servoThread;

    // // Start motor movement
    // int motorParams[] = {1000, 1500};
    // pthread_create(&motorThread, NULL, forwardDriveThread, (void*) motorParams);
    
    // // Start servo movement
    // ServoParams servoValues[] = {
    //     {servos.elbow, get_servo_position(servos.elbow), elbowPos.perpendicularToShoulder, 10},
    //     {servos.wrist, get_servo_position(servos.wrist), wristPos.perpendicularUpwards, 10}
    // };
    // ServoThreadArgs servoArgs = {servoValues, 2};
    // pthread_create(&servoThread, NULL, runServoThreads, (void*) servoParams);

    // // Wait for the threads to finish
    // pthread_join(motorThread, NULL);
    // pthread_join(servoThread, NULL);

    // // Clean up
    // pthread_cancel(motorThread);
    // pthread_cancel(servoThread);
    // disable_servos();
    // printf("All threads finished.\n");


    disable_servos();
    return 0;
}