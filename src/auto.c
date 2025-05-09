#include "../include/library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define TAPE_THRESHOLD 1500
#define DEGREES_TO_TICKS 9.013888889
#define STRAFE_CM_TO_TICKS 143.614670791
#define STRAIGHT_CM_TO_TICKS 232.216295546
#define MAX_COMMAND_LENGTH 100

#define RESET_COLOR "\033[0m"
#define GREEN_COLOR "\033[32m"
#define RED_COLOR "\033[31m"
#define YELLOW_COLOR "\033[33m"
#define CYAN_COLOR "\033[36m"
#define MAGENTA_COLOR "\033[35m"

void displayWelcomeHeader();
void displayPrompt();
void displaySuccess(const char *message);
void driveDirection(const char *params);

// Function prototypes for commands
void executeCommand(const char *command, const char *params);
void turnRight(const char *params);
void turnLeft(const char *params);
void driveForward(const char *params);
void driveBackward(const char *params);
void driveRight(const char *params);
void driveLeft(const char *params);
void lowerArm(const char *params);
void moveArm(const char *params);
void newServoPos(const char *params);
void strafeArm(const char *params);
void pvcArm(const char *params);
void potatoArm(const char *params);
void groundArm(const char *params);
void openPos(const char *params);
void closePos(const char *params);
void closeBox(const char *params);
void helpCommand(const char *params);
void clearCommand(const char *params);
void batteryLevel(const char *params);

// Command structure
typedef struct {
    const char *name;
    void (*execute)(const char *params);
} Command;

// Command table
const Command commandTable[] = {
    {"turnRight", turnRight},
    {"tr", turnRight}, // Alias for turnRight
    {"turnLeft", turnLeft},
    {"tl", turnLeft}, // Alias for turnLeft
    {"driveForward", driveForward},
    {"df", driveForward}, // Alias for driveForward
    {"driveBackward", driveBackward},
    {"db", driveBackward}, // Alias for driveBackward
    {"driveRight", driveRight},
    {"dr", driveRight}, // Alias for driveRight
    {"driveLeft", driveLeft},
    {"dl", driveLeft}, // Alias for driveLeft
    {"lowerArm", lowerArm},
    {"la", lowerArm}, // Alias for lowerArm
    {"moveArm", moveArm},
    {"ma", moveArm}, // Alias for moveArm
    {"moveServo", newServoPos},
    {"ms", newServoPos}, // Alias for moveServo
    {"strafePos", strafeArm},
    {"sp", strafeArm}, // Alias for strafePos
    {"pvcPos", pvcArm},
    {"pvc", pvcArm}, // Alias for pvcPos
    {"potatoPos", potatoArm},
    {"pp", potatoArm}, // Alias for potatoPos
    {"groundPos", groundArm},
    {"gp", groundArm}, // Alias for groundPos
    {"openPos", openPos},
    {"op", openPos}, // Alias for openPos
    {"closePos", closePos},
    {"cp", closePos}, // Alias for closePos
    {"closeBox", closeBox},
    {"cb", closeBox}, // Alias for closeBox
    {"battery", batteryLevel},
    {"b", batteryLevel}, // Alias for battery
    {"help", helpCommand},
    {"h", helpCommand}, // Alias for help
    {"ls", helpCommand}, // Alias for help
    {"clear", clearCommand},
    {"c", clearCommand}, // Alias for clear
    {"driveDirection", driveDirection},
    {"dd", driveDirection}, // Alias for driveDirection
    {"exit", NULL},
    {"quit", NULL},
    {NULL, NULL}
};

int main() {
    char input[MAX_COMMAND_LENGTH];
    char command[50];
    char params[MAX_COMMAND_LENGTH - 50];

    displayWelcomeHeader();

    while (1) {
        displayPrompt();
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit on EOF or error
        }

        // Parse the input into command and parameters
        if (sscanf(input, "%s %[^\n]", command, params) < 1) {
            continue; // Skip empty input
        }

        if ((strcmp(command, "exit") == 0) || (strcmp(command, "quit") == 0)) {
            displaySuccess("Exiting Manual Control Mode. Goodbye!");
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
            printf(GREEN_COLOR "Executing command: %s\n" RESET_COLOR, command);
            commandTable[i].execute(params);
            return;
        }
    }

    // Print an error message for unknown commands
    printf(RED_COLOR "Error: Unknown command '%s'. Please try again.\n" RESET_COLOR, command);
}


/* ##################################################################
|  Command Implementations
| ################################################################### */

void turnRight(const char *params) {
    for (int i = 0; i < 4; i++) {
        cmpc(i);
    }
    int speed = atoi(params);
    printf("Input Speed: %d.\n", speed);
    if (speed < 0) {
        printf("Invalid speed for turnRight. Speed must be positive.\n");
        return;
    }
    else {
        move_at_velocity(wheels.frontLeft, -speed);
        move_at_velocity(wheels.backLeft, -speed);
        move_at_velocity(wheels.frontRight, speed);
        move_at_velocity(wheels.backRight, speed);
    }
    char input;
    int distance;
    while (1) {
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == '\n') {
                break; // Exit the loop on Enter key
            }
        }
        msleep(10);
    }
    printf("Stopping rotation.\n");
    distance = (int)((get_motor_position_counter(wheels.frontLeft)+get_motor_position_counter(wheels.frontRight)+get_motor_position_counter(wheels.backLeft)+get_motor_position_counter(wheels.backRight)) / DEGREES_TO_TICKS / 4);
    move_at_velocity(wheels.frontLeft, speed);
    move_at_velocity(wheels.backLeft, speed);
    move_at_velocity(wheels.frontRight, -speed);
    move_at_velocity(wheels.backRight, -speed);
    msleep(30);
    ao();
    printf("Turned %d degrees at speed %d.\n", abs(distance), speed);
    printf("-------------------------------\n");
    return;
}

void turnLeft(const char *params) {
    for (int i = 0; i < 4; i++) {
        cmpc(i);
    }
    int speed = atoi(params);
    printf("Input Speed: %d.\n", speed);
    if (speed < 0) {
        printf("Invalid speed for turnLeft. Speed must be positive.\n");
        return;
    }
    else {
        move_at_velocity(wheels.frontLeft, speed);
        move_at_velocity(wheels.backLeft, speed);
        move_at_velocity(wheels.frontRight, -speed);
        move_at_velocity(wheels.backRight, -speed);
    }
    char input;
    int distance;
    while (1) {
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == '\n') {
                break; // Exit the loop on Enter key
            }
        }
        msleep(10);
    }
    printf("Stopping rotation.\n");
    distance = (int)(get_motor_position_counter(wheels.frontLeft) / DEGREES_TO_TICKS);
    move_at_velocity(wheels.frontLeft, -speed);
    move_at_velocity(wheels.backLeft, -speed);
    move_at_velocity(wheels.frontRight, speed);
    move_at_velocity(wheels.backRight, speed);
    msleep(30);
    ao();
    printf("Turned %d degrees at speed %d.\n", abs(distance), speed);
    printf("-------------------------------\n");
    return;
}

// void driveForward(const char *params) {
//     for (int i = 0; i < 4; i++) {
//         cmpc(i);
//     }
//     int speed = atoi(params);
//     mav(wheels.frontLeft, speed);
//     mav(wheels.backLeft, speed);
//     mav(wheels.frontRight, speed);
//     mav(wheels.backRight, speed);
//     char input;
//     int distance;
//     while (1) {
//         if (read(STDIN_FILENO, &input, 1) == 1) {
//             if (input == '\n') {
//                 break; // Exit the loop on Enter key
//             }
//         }
//         msleep(10);
//     }
//     printf("Stopping forward drive.\n");
//     distance = (int)(get_motor_position_counter(wheels.frontLeft));
//     stop(speed);
//     printf("Drove forward %d ticks at speed %d.\n", abs(distance), speed);
//     printf("-------------------------------\n");
//     return;
// }

void driveForward(const char *params) {
    int speed;
    float distance;
    if (sscanf(params, "%d %f", &speed, &distance) == 2)
    {
        if (speed > 0 && distance > 0) {
            forwardDrive(distance * STRAIGHT_CM_TO_TICKS, speed);
            printf("Drove forward %f inches at speed %d.\n", distance, speed);
        } else {
            printf("Invalid parameters for drive_forward.\nUsage: drive_forward <speed> <distance>\n");
        }
    }
    else
    {
        printf("Invalid parameters for drive_forward.\nUsage: drive_forward <speed> <distance>\n");
    }
}

void driveBackward(const char *params) {
    for (int i = 0; i < 4; i++) {
        cmpc(i);
    }
    int speed = atoi(params);
    mav(wheels.frontLeft, -speed);
    mav(wheels.backLeft, -speed);
    mav(wheels.frontRight, -speed);
    mav(wheels.backRight, -speed);
    char input;
    int distance;
    while (1) {
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == '\n') {
                break; // Exit the loop on Enter key
            }
        }
        msleep(10);
    }
    printf("Stopping backward drive.\n");
    distance = (int)(get_motor_position_counter(wheels.frontLeft));
    stop(-speed);
    printf("Drove backward %d ticks at speed %d.\n", abs(distance), speed);
    printf("-------------------------------\n");
    return;
}

void driveRight(const char *params) {
    for (int i = 0; i < 4; i++) {
        cmpc(i);
    }
    int speed = atoi(params);
    mav(wheels.frontLeft, -speed);
    mav(wheels.backLeft, speed);
    mav(wheels.frontRight, speed);
    mav(wheels.backRight, -speed);
    char input;
    int distance;
    while (1) {
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == '\n') {
                break; // Exit the loop on Enter key
            }
        }
        msleep(10);
    }
    printf("Stopping right drive.\n");
    distance = (int)(get_motor_position_counter(wheels.frontLeft));
    mav(wheels.frontLeft, speed);
    mav(wheels.backLeft, -speed);
    mav(wheels.frontRight, -speed);
    mav(wheels.backRight, speed);
    msleep(30);
    ao();
    printf("Drove right %d ticks at speed %d.\n", abs(distance), speed);
    printf("-------------------------------\n");
    return;
}

void driveLeft(const char *params) {
    for (int i = 0; i < 4; i++) {
        cmpc(i);
    }
    int speed = atoi(params);
    mav(wheels.frontLeft, speed);
    mav(wheels.backLeft, -speed);
    mav(wheels.frontRight, -speed);
    mav(wheels.backRight, speed);
    char input;
    int distance;
    while (1) {
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == '\n') {
                break; // Exit the loop on Enter key
            }
        }
        msleep(10);
    }
    printf("Stopping left drive.\n");
    distance = (int)(get_motor_position_counter(wheels.frontLeft));
    mav(wheels.frontLeft, -speed);
    mav(wheels.backLeft, speed);
    mav(wheels.frontRight, speed);
    mav(wheels.backRight, -speed);
    msleep(30);
    ao();
    printf("Drove left %d ticks at speed %d.\n", abs(distance), speed);
    printf("-------------------------------\n");
    return;
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

void newServoPos(const char *params) {
    char servoName[50];
    int position;
    if (sscanf(params, "%s %d", servoName, &position) == 2) {
        if (strcmp(servoName, "shoulder") == 0) {
            set_servo_position(servos.shoulder, position);
        } else if (strcmp(servoName, "elbow") == 0) {
            set_servo_position(servos.elbow, position);
        } else if (strcmp(servoName, "wrist") == 0) {
            set_servo_position(servos.wrist, position);
        } else if (strcmp(servoName, "claw") == 0) {
            set_servo_position(servos.claw, position);
        } else {
            printf("Invalid servo name. Usage: move_servo <servo_name> <position>\n");
            return;
        }
        printf("Moved servo %s to position %d\n", servoName, position);
    } else {
        printf("Invalid parameters for move_servo. Usage: move_servo <servo_name> <position>\n");
    }
}

void strafeArm(const char *params) {
    // No parameters needed for this command
    runServoThreads((ServoParams[]){
        {servos.shoulder, shoulderPos.strafe, 2},
        {servos.elbow, 100, 1},
        {servos.wrist, wristPos.strafe, 2}},
    3);
    msleep(1500);
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
        {servos.elbow, elbowPos.perpendicularToShoulder, 2},
        {servos.wrist, wristPos.ground, 2},
    }, 3);
    msleep(1000);
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

void helpCommand(const char *params) {
    printf(CYAN_COLOR "Available Commands (with aliases):\n" RESET_COLOR);
    printf(MAGENTA_COLOR " - turnRight (tr) <speed> <degrees>\n" RESET_COLOR);
    printf(MAGENTA_COLOR " - turnLeft (tl) <speed> <degrees>\n" RESET_COLOR);
    printf(MAGENTA_COLOR " - driveForward (df) <distance>\n" RESET_COLOR);
    printf(MAGENTA_COLOR " - driveBackward (db) <distance>\n" RESET_COLOR);
    printf(MAGENTA_COLOR " - driveRight (dr) <distance>\n" RESET_COLOR);
    printf(MAGENTA_COLOR " - driveLeft (dl) <distance>\n" RESET_COLOR);
    printf(GREEN_COLOR " - lowerArm (la)\n" RESET_COLOR);
    printf(GREEN_COLOR " - moveArm (ma) <shoulder> <elbow> <wrist>\n" RESET_COLOR);
    printf(GREEN_COLOR " - strafePos (sp)\n" RESET_COLOR);
    printf(GREEN_COLOR " - pvcPos (pvc)\n" RESET_COLOR);
    printf(GREEN_COLOR " - potatoPos (pp)\n" RESET_COLOR);
    printf(GREEN_COLOR " - groundPos (gp)\n" RESET_COLOR);
    printf(GREEN_COLOR " - openPos (op)\n" RESET_COLOR);
    printf(GREEN_COLOR " - closePos (cp) <0|1>\n" RESET_COLOR);
    printf(GREEN_COLOR " - closeBox (cb)\n" RESET_COLOR);
    printf(GREEN_COLOR " - battery (b)\n" RESET_COLOR);
    printf(GREEN_COLOR " - help (h)\n" RESET_COLOR);
    printf(GREEN_COLOR " - clear (c)\n" RESET_COLOR);
    printf(MAGENTA_COLOR " - driveDirection (dd) <direction> <distance> <speed>\n" RESET_COLOR);
    printf(GREEN_COLOR " - exit (exit)\n" RESET_COLOR);
    printf(CYAN_COLOR "Type 'exit' to quit the program.\n" RESET_COLOR);
}

void clearCommand(const char *params) {
    displayWelcomeHeader();
}

void batteryLevel(const char *params) {
    float battery = power_level() * 100;
    if (battery_charging()) {
        printf(GREEN_COLOR "Battery is charging.\n" RESET_COLOR);
    } else {
        printf(RED_COLOR "Battery is not charging.\n" RESET_COLOR);
    }
    printf("Battery level: %.2f%%\n", battery); // Rounds to 2 decimal places
}

void displayWelcomeHeader() {
    system("clear");
    // Display a colorful welcome header with ASCII art
    printf(CYAN_COLOR "==============================================================\n");
    printf("   " GREEN_COLOR "██████╗  ██████╗ ████████╗██████╗  █████╗ ██╗     ██╗     \n");
    printf("   ██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗██╔══██╗██║     ██║     \n");
    printf("   ██████╔╝██║   ██║   ██║   ██████╔╝███████║██║     ██║     \n");
    printf("   ██╔══██╗██║   ██║   ██║   ██╔══██╗██╔══██║██║     ██║     \n");
    printf("   ██████╔╝╚██████╔╝   ██║   ██████╔╝██║  ██║███████╗███████╗\n");
    printf("   ╚═════╝  ╚═════╝    ╚═╝   ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝\n" RESET_COLOR);
    printf(CYAN_COLOR "==============================================================\n");
    printf("   Welcome to " GREEN_COLOR "Autonomous Mode\n");
    printf(CYAN_COLOR "   Select a command to test\n");
    printf("==============================================================\n" RESET_COLOR);
}

void displayPrompt() {
    printf(YELLOW_COLOR "\n[COMMAND]> " RESET_COLOR);
}

void displaySuccess(const char *message) {
    printf(GREEN_COLOR "%s\n" RESET_COLOR, message);
}

void driveDirection(const char *params) {
    int direction, speed;
    for (int i = 0; i < 4; i++) {
        cmpc(i);
    }
    if (sscanf(params, "%d %d", &direction, &speed) == 2) {
        if (direction < 0) {
            direction = (direction % 360 + 360) % 360; // Convert negative direction to positive
        }
        if (direction >= 0 && direction <= 360 && speed > 0) {
            // Calculate wheel speeds based on direction
            double rad = direction * (M_PI / 180.0);
            double cos_dir = cos(rad);
            double sin_dir = sin(rad);

            int frontLeftSpeed = (int)(speed * (cos_dir - sin_dir));
            int frontRightSpeed = (int)(speed * (cos_dir + sin_dir));
            int rearLeftSpeed = (int)(speed * (cos_dir + sin_dir));
            int rearRightSpeed = (int)(speed * (cos_dir - sin_dir));
            int values[] = {frontLeftSpeed, frontRightSpeed, rearLeftSpeed, rearRightSpeed};

            // Find the maximum calculated speed
            int maxSpeed = fmax(values[0], fmax(values[1], fmax(values[2], values[3])));

            // Calculate the scaling factor
            double scaleFactor = 1.0;
            if (maxSpeed > 1500) {
                scaleFactor = 1500.0 / maxSpeed;
            }
            printf("scaleFactor: %f,\n", scaleFactor);
            printf("maxSpeed: %d,\n", maxSpeed);

            // Apply the scaling factor to all speeds
            frontLeftSpeed = (int)(frontLeftSpeed * scaleFactor);
            frontRightSpeed = (int)(frontRightSpeed * scaleFactor);
            rearLeftSpeed = (int)(rearLeftSpeed * scaleFactor);
            rearRightSpeed = (int)(rearRightSpeed * scaleFactor);
            printf("frontLeftSpeed: %d,\nfrontRightSpeed: %d,\nrearLeftSpeed: %d,\nrearRightSpeed: %d,\n", frontLeftSpeed, frontRightSpeed, rearLeftSpeed, rearRightSpeed);

            // Call the appropriate drive functions
            move_at_velocity(wheels.frontLeft, frontLeftSpeed);
            move_at_velocity(wheels.frontRight, frontRightSpeed);
            move_at_velocity(wheels.backLeft, rearLeftSpeed);
            move_at_velocity(wheels.backRight, rearRightSpeed);
            
            char input;
            int distance;
            while (1) {
                if (read(STDIN_FILENO, &input, 1) == 1) {
                    if (input == '\n') {
                        break; // Exit the loop on Enter key
                    }
                }
                msleep(10);
            }
            printf("Stopping drive.\n");
            distance = (int)(get_motor_position_counter(wheels.frontLeft));
            mav(wheels.frontLeft, (-1) * frontLeftSpeed);
            mav(wheels.frontRight, (-1) * frontRightSpeed);
            mav(wheels.backLeft, (-1) * rearLeftSpeed);
            mav(wheels.backRight, (-1) * rearRightSpeed);
            msleep(30);
            alloff(); // Stop the motors
            printf("Drove in direction %d for %d units at speed %d.\n", direction, distance, speed);

        } else {
            printf("Invalid parameters for driveDirection. Usage: driveDirection <direction> <distance> <speed>\n");
        }
    } else {
        printf("Invalid parameters for driveDirection. Usage: driveDirection <direction> <distance> <speed>\n");
    }
}