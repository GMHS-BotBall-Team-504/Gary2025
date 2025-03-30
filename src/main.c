#include <kipr/wombat.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../include/library.h"
#define startingDirection 180
#define sum 2450

// Struct to hold parameters for servoPosition
typedef struct {
    int port;
    int startPosition;
    int endPosition;
    int stepDelay;
} ServoParams;

// Define a barrier for synchronization
pthread_barrier_t servoBarrier;

// Thread function to move the servo gradually
void* servoThread(void* dataPtr) {
    ServoParams* params = (ServoParams*)dataPtr;

    // Wait at the barrier until all threads are ready
    pthread_barrier_wait(&servoBarrier);

    // Determine the direction of movement
    int step = (params->endPosition > params->startPosition) ? 15 : -15; // Step size
    int currentPosition = params->startPosition;

    // Gradually move the servo to the target position
    while ((step > 0 && currentPosition < params->endPosition) || 
           (step < 0 && currentPosition > params->endPosition)) {
        currentPosition += step;

        // Prevent overshooting
        if ((step > 0 && currentPosition > params->endPosition) || 
            (step < 0 && currentPosition < params->endPosition)) {
            currentPosition = params->endPosition;
        }

        set_servo_position(params->port, currentPosition);
        msleep(params->stepDelay);
    }

    return NULL;
}

// Function to run servo threads with gradual movement
void runServoThreads(ServoParams params[], int numServos) {
    pthread_t threads[3]; // Array to hold thread IDs (up to 3)

    // Initialize the barrier for the number of servos
    pthread_barrier_init(&servoBarrier, NULL, numServos);

    // Create threads for each servo
    for (int i = 0; i < numServos; i++) {
        pthread_create(&threads[i], NULL, servoThread, &params[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < numServos; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the barrier
    pthread_barrier_destroy(&servoBarrier);
}

int main() {
    
    // enable_servos();
    rotate(5000, 1500);
    msleep(1000);
    // // Example 1: Move three servos to the first set of positions gradually
    // printf("Moving to first positions gradually...\n");
    // runServoThreads((ServoParams[]) {
    //     {3, get_servo_position(3), 1600, 2},
    //     {2, get_servo_position(2), sum - 1600, 2},
    //     {1, get_servo_position(1), 200, 5}
    // }, 3); // Pass an anonymous array and the number of servos
    // msleep(1500);

    // // Example 2: Move three servos to the second set of positions gradually
    // printf("Moving to second positions gradually...\n");
    // runServoThreads((ServoParams[]) {
    //     {3, get_servo_position(3), 600, 2},
    //     {2, get_servo_position(2), sum - 600, 2},
    //     {1, get_servo_position(1), 2000, 5}
    // }, 3); // Pass another anonymous array and the number of servos
    // msleep(600);

    // set_servo_position(0, 150);
    // msleep(300);
    // set_servo_position(0, 1300);
    // msleep(300);
    // disable_servos();
    return 0;
}