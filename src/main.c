#include <kipr/wombat.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define startingDirection 180

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int tripCount;
} CustomBarrier;

void custom_barrier_init(CustomBarrier* barrier, int tripCount) {
    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->cond, NULL);
    barrier->count = 0;
    barrier->tripCount = tripCount;
}

void custom_barrier_wait(CustomBarrier* barrier) {
    pthread_mutex_lock(&barrier->mutex);
    barrier->count++;
    if (barrier->count >= barrier->tripCount) {
        barrier->count = 0; // Reset for reuse
        pthread_cond_broadcast(&barrier->cond);
    } else {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    }
    pthread_mutex_unlock(&barrier->mutex);
}

void custom_barrier_destroy(CustomBarrier* barrier) {
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);
}

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
    int step = (params->endPosition > params->startPosition) ? 5 : -5; // <--- change step size
    int currentPosition = params->startPosition;

    // Gradually move the servo to the target position
    while ((step > 0 && currentPosition < params->endPosition) || 
           (step < 0 && currentPosition > params->endPosition)) {
        currentPosition += step;

        // overshooting check
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
void runServoThreads(int port1, int start1, int end1, int port2, int start2, int end2, int port3, int start3, int end3, int stepDelay) {
    pthread_t thread1, thread2, thread3;

    // Initialize the barrier for 3 threads
    pthread_barrier_init(&servoBarrier, NULL, 3);

    // Define parameters for each servo movement
    ServoParams servo1 = {port1, start1, end1, stepDelay};
    ServoParams servo2 = {port2, start2, end2, stepDelay};
    ServoParams servo3 = {port3, start3, end3, stepDelay};

    // Create threads to run servo movements simultaneously
    pthread_create(&thread1, NULL, servoThread, &servo1);
    pthread_create(&thread2, NULL, servoThread, &servo2);
    pthread_create(&thread3, NULL, servoThread, &servo3);

    // Wait for all threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Destroy the barrier
    pthread_barrier_destroy(&servoBarrier);
}

int main() {
    enable_servos();

    // Example 1: Move three servos to the first set of positions gradually
    printf("Moving to first positions gradually...\n");
    int position1 = 1786;
    int position2 = 1930 - position1;
    int position3 = 200; // Add position for the third servo
    runServoThreads(3, get_servo_position(3), position1, 2, get_servo_position(2), position2, 1, get_servo_position(1), position3, 5);
    msleep(1000);

    // Example 2: Move three servos to the second set of positions gradually
    printf("Moving to second positions gradually...\n");
    position1 = 350;
    position2 = 1930 - position1;
    position3 = 1600; // Add position for the third servo
    runServoThreads(3, get_servo_position(3), position1, 2, get_servo_position(2), position2, 1, get_servo_position(1), position3, 5);
    msleep(600);

    disable_servos();
    return 0;
}