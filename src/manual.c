#include "../include/library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define TAPE_THRESHOLD 1500
#define DEGREES_TO_TICKS 9.013888889
#define STRAFE_CM_TO_TICKS 143.614670791
#define STRAIGHT_CM_TO_TICKS 130.0000
#define MAX_COMMAND_LENGTH 100

// Function prototypes for commands
void turnRight(const char *params);
void turnLeft(const char *params);
void driveForward(const char *params);
void driveBackward(const char *params);
void driveRight(const char *params);
void driveLeft(const char *params);
void lowerArm(const char *params);
void moveArm(const char *params);
void strafeArm(const char *params);
void pvcArm(const char *params);
void potatoArm(const char *params);
void groundArm(const char *params);
void openPos(const char *params);
void closePos(const char *params);
void closeBox(const char *params);

// Command structure
typedef struct {
    const char *name;
    void (*execute)(const char *params);
} Command;

// Command table
const Command commandTable[] = {
    {"turnRight", turnRight},
    {"turnLeft", turnLeft},
    {"driveForward", driveForward},
    {"driveBackward", driveBackward},
    {"driveRight", driveRight},
    {"driveLeft", driveLeft},
    {"lowerArm", lowerArm},
    {"moveArm", moveArm},
    {"strafePos", strafeArm},
    {"pvcPos", pvcArm},
    {"potatoPos", potatoArm},
    {"groundPos", groundArm},
    {"openPos", openPos},
    {"closePos", closePos},
    {"closeBox", closeBox},
    {NULL, NULL}
};

void executeCommand(const char *command, const char *params);

int main() {
    char input[MAX_COMMAND_LENGTH];
    char command[50];
    char params[MAX_COMMAND_LENGTH - 50];

    printf("Manual control mode. Enter commands (type 'exit' to quit):\n");

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit on EOF or error
        }

        // Parse the input into command and parameters
        if (sscanf(input, "%s %[^\n]", command, params) < 1) {
            continue; // Skip empty input
        }

        if (strcmp(command, "exit") == 0) {
            printf("Exiting manual control mode.\n");
            break;
        }

        // Execute the command
        executeCommand(command, params);
    }

    return 0;
}

void executeCommand(const char *command, const char *params) {
    for (int i = 0; commandTable[i].name != NULL; i++) {
        if (strcmp(command, commandTable[i].name) == 0) {
            commandTable[i].execute(params);
            return;
        }
    }
    printf("Unknown command: %s\n", command);
}


/* ##################################################################
|  Command Implementations
| ################################################################### */

void turnRight(const char *params) {
    int degrees = atoi(params); // Convert parameter to integer
    if (degrees > 0) {
        rotate(DEGREES_TO_TICKS * -degrees, -1000);
        printf("Turned right %d degrees.\n", degrees);
    } else {
        printf("Invalid parameters for turn_right. Usage: turn_right <degrees>\n");
    }
}

void turnLeft(const char *params) {
    int degrees = atoi(params); // Convert parameter to integer
    if (degrees > 0) {
        rotate(DEGREES_TO_TICKS * degrees, 1000);
        printf("Turned left %d degrees.\n", degrees);
    } else {
        printf("Invalid parameters for turn_left. Usage: turn_left <degrees>\n");
    }
}

void driveForward(const char *params) {
    int distance = atoi(params); // Convert parameter to integer
    if (distance > 0) {
        forwardDrive(distance, 1500);
        printf("Drove forward %d units.\n", distance);
    } else {
        printf("Invalid parameters for drive_forward. Usage: drive_forward <distance>\n");
    }
}

void driveBackward(const char *params) {
    int distance = atoi(params); // Convert parameter to integer
    if (distance > 0) {
        backwardDrive(distance, 1500);
        printf("Drove forward %d units.\n", distance);
    } else {
        printf("Invalid parameters for drive_forward. Usage: drive_forward <distance>\n");
    }
}

void driveRight(const char *params) {
    int distance = atoi(params); // Convert parameter to integer
    if (distance > 0) {
        rightDrive(distance, 1500);
        printf("Drove right %d units.\n", distance);
    } else {
        printf("Invalid parameters for drive_forward. Usage: drive_forward <distance>\n");
    }
}

void driveLeft(const char *params) {
    int distance = atoi(params); // Convert parameter to integer
    if (distance > 0) {
        leftDrive(distance, 1500);
        printf("Drove left %d units.\n", distance);
    } else {
        printf("Invalid parameters for drive_forward. Usage: drive_forward <distance>\n");
    }
}

void lowerArm(const char *params) {
    // No parameters needed for this command
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.ground, 2},
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2}
    }, 3);
    printf("Lowered arm.\n");
}

void moveArm(const char *params) {
    int shoulder, elbow, wrist;
    if (sscanf(params, "%d %d %d", &shoulder, &elbow, &wrist) == 3) {
        runServoThreads((ServoParams[]) {
            {servos.shoulder, shoulder, 2},
            {servos.elbow, elbow, 2},
            {servos.wrist, wrist, 2}
        }, 3);
        printf("Moved arm to positions - Shoulder: %d, Elbow: %d, Wrist: %d\n", shoulder, elbow, wrist);
    } else {
        printf("Invalid parameters for move_arm. Usage: move_arm <shoulder> <elbow> <wrist>\n");
    }
}

void strafeArm(const char *params) {
    // No parameters needed for this command
    runServoThreads((ServoParams[]){
            {servos.shoulder, shoulderPos.strafe, 2},
            {servos.elbow, 400, 2},
            {servos.wrist, wristPos.strafe, 2}},
        3);
    msleep(500);
    runServoThreads((ServoParams[]){
                        {servos.shoulder, shoulderPos.strafe, 2},
                        {servos.elbow, elbowPos.strafe, 2}},
                    2);
    printf("Strafe arm position.\n");
    return;
}

void pvcArm(const char *params) {
    // No parameters needed for this command
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.PVC, 2},
        {servos.elbow, elbowPos.PVC, 2},
        {servos.wrist, wristPos.PVC, 2}
    }, 3);
    printf("PVC arm position.\n");
    return;
}

void potatoArm(const char *params) {
    // No parameters needed for this command
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.potato, 2},
        {servos.elbow, elbowPos.potato, 2},
        {servos.wrist, wristPos.potato, 2}
    }, 3);
    printf("Potato arm position.\n");
    return;
}

void groundArm(const char *params) {
    runServoThreads((ServoParams[]) {
        {servos.shoulder, shoulderPos.ground, 2},
        {servos.elbow, elbowPos.ground, 2},
        {servos.wrist, wristPos.ground, 2},
    }, 3);
    printf("Ground claw.\n");
    return;
}

void openPos(const char *params) {
    openClaw();
    return;
}

void closePos(const char *params) {
    int position = atoi(params);
    if (position == 0) {
        closeClaw(0);
    }
    else {
        closeClaw(1);
    }
    printf("Closed claw.\n");
    return;
}

void closeBox(const char *params) {
    enable_servo(servos.claw);
    set_servo_position(servos.claw, clawPos.closedBox);
    msleep(500);
    printf("Closed claw to Box.\n");
}