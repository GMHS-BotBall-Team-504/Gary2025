#include "../include/library.h"
#include <stdio.h>



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

void* runServoThreadsWrapper(void* arg) {
    ServoThreadArgs* args = (ServoThreadArgs*) arg;
    runServoThreads(args->params, args->count);
    return NULL;
}

void executeMovementandServoThreads(int motorParams[], ServoThreadArgs* servoArgs) {
    pthread_t motorThread, servoThread; // Declare thread variables locally

    // Start the motor thread
    pthread_create(&motorThread, NULL, forwardDriveThread, (void*) motorParams);

    // Start the servo thread
    pthread_create(&servoThread, NULL, runServoThreadsWrapper, (void*) servoArgs);

    // Wait for the motor thread to finish
    pthread_join(motorThread, NULL);
    pthread_join(servoThread, NULL);

    // Clean up
    disable_servos();
    printf("All threads finished.\n");
}



