#ifndef THREADS_H
#define THREADS_H

typedef struct {
    ServoParams* params; // Pointer to the array of ServoParams
    int count;           // Number of servos to move
} ServoThreadArgs;

void* forwardDriveThread(void* arg);
void* runServoThreadsWrapper(void* arg);
void executeMovementandServoThreads(int motorParams[], ServoThreadArgs* servoArgs);

#endif // THREADS_H