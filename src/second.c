#include "../include/second.h"

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
    int speed, degrees;
    if (sscanf(params, "%d %d", &speed, &degrees) == 2) {
        if (speed > 0 && degrees > 0) {
            rotate(DEGREES_TO_TICKS * -degrees, -speed);
            printf("Turned right %d degrees at speed %d.\n", degrees, speed);
        } else {
            printf("Invalid parameters for turn_right.\nUsage: turn_right <speed> <degrees>\n");
        }
    } else if (sscanf(params, "%d", &degrees) == 1) {
        if (degrees > 0) {
            rotate(DEGREES_TO_TICKS * -degrees, -1500);
            printf("Turned right %d degrees at speed 1500.\n", degrees);
        } else {
            printf("Invalid parameters for turn_right.\nUsage: turn_right <degrees>\n");
        }
    } else {
        printf("Invalid parameters for turn_right.\nUsage: turn_right <speed> <degrees>\n");
    }
}

void turnLeft(const char *params) {
    int speed, degrees;
    if (sscanf(params, "%d %d", &speed, &degrees) == 2) {
        if (speed > 0 && degrees > 0) {
            rotate(DEGREES_TO_TICKS * degrees, speed);
            printf("Turned left %d degrees at speed %d.\n", degrees, speed);
        } else {
            printf("Invalid parameters for turn_left. Usage: turn_left <speed> <degrees>\n");
        }
    } else if (sscanf(params, "%d", &degrees) == 1) {
        if (degrees > 0) {
            rotate(DEGREES_TO_TICKS * degrees, 1500);
            printf("Turned left %d degrees at speed 1500.\n", degrees);
        } else {
            printf("Invalid parameters for turn_left. Usage: turn_left <degrees>\n");
        }
    } else {
        printf("Invalid parameters for turn_left. Usage: turn_left <speed> <degrees>\n");
    }
}

void driveForward(const char *params) {
    int speed, distance;
    if (sscanf(params, "%d %d", &speed, &distance) == 2) {
        if (speed > 0 && distance > 0) {
            forwardDrive(distance * STRAIGHT_CM_TO_TICKS, speed);
            printf("Drove forward %d inches at speed %d.\n", distance, speed);
        } else {
            printf("Invalid parameters for drive_forward.\nUsage: drive_forward <speed> <distance>\n");
        }
    } else {
        printf("Invalid parameters for drive_forward.\nUsage: drive_forward <speed> <distance>\n");
    }
}

void driveBackward(const char *params) {
    int speed, distance;
    if (sscanf(params, "%d %d", &speed, &distance) == 2) {
        if (speed > 0 && distance > 0) {
            backwardDrive(distance * STRAIGHT_CM_TO_TICKS, speed);
            printf("Drove backward %d inches at speed %d.\n", distance, speed);
        } else {
            printf("Invalid parameters for drive_backward.\nUsage: drive_backward <speed> <distance>\n");
        }
    } else {
        printf("Invalid parameters for drive_backward.\nUsage: drive_backward <speed> <distance>\n");
    }
}

void driveRight(const char *params) {
    int speed, distance;
    if (sscanf(params, "%d %d", &speed, &distance) == 2) {
        if (speed > 0 && distance > 0) {
            rightDrive(distance * STRAFE_CM_TO_TICKS, speed);
            printf("Drove right %d units at speed %d.\n", distance, speed);
        } else {
            printf("Invalid parameters for drive_right.\nUsage: drive_right <speed> <distance>\n");
        }
    } else {
        printf("Invalid parameters for drive_right.\nUsage: drive_right <speed> <distance>\n");
    }
}

void driveLeft(const char *params) {
    int speed, distance;
    if (sscanf(params, "%d %d", &speed, &distance) == 2) {
        if (speed > 0 && distance > 0) {
            leftDrive(distance * STRAFE_CM_TO_TICKS, speed);
            printf("Drove left %d units at speed %d.\n", distance, speed);
        } else {
            printf("Invalid parameters for drive_left. Usage: drive_left <speed> <distance>\n");
        }
    } else {
        printf("Invalid parameters for drive_left. Usage: drive_left <speed> <distance>\n");
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
    msleep(1700);
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

void helpCommand(const char *params) {
    printf("YOU'RE ON MANUAL");
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
    printf("Battery level: %.2f%%\n", battery); // Rounds to 2 decimal places
}

void displayWelcomeHeader() {
    system("clear");
    printf(CYAN_COLOR "==============================================================\n");
    printf("   " GREEN_COLOR "██████╗  ██████╗ ████████╗██████╗  █████╗ ██╗     ██╗     \n");
    printf("   ██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗██╔══██╗██║     ██║     \n");
    printf("   ██████╔╝██║   ██║   ██║   ██████╔╝███████║██║     ██║     \n");
    printf("   ██╔══██╗██║   ██║   ██║   ██╔══██╗██╔══██║██║     ██║     \n");
    printf("   ██████╔╝╚██████╔╝   ██║   ██████╔╝██║  ██║███████╗███████╗\n");
    printf("   ╚═════╝  ╚═════╝    ╚═╝   ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝\n" RESET_COLOR);
    printf(CYAN_COLOR "==============================================================\n");
    printf("   Welcome to " GREEN_COLOR "nards Control Mode\n");
    printf(CYAN_COLOR "   Enter commands (type 'exit' or 'quit')\n");
    printf("==============================================================\n" RESET_COLOR);
    printf(YELLOW_COLOR "Available Commands: Type 'help' or 'h' to see the list.\n" RESET_COLOR);
}

void displayPrompt() {
    printf(YELLOW_COLOR "\n[COMMAND]> " RESET_COLOR);
}

void displaySuccess(const char *message) {
    printf(GREEN_COLOR "%s\n" RESET_COLOR, message);
}

void driveDirection(const char *params) {

    int direction, distance, speed;
    if (sscanf(params, "%d %d %d", &direction, &distance, &speed) == 3) {
        if (direction < 0) {
            direction = (direction % 360 + 360) % 360; // Convert negative direction to positive
        }
        if (direction >= 0 && direction <= 360 && distance > 0 && speed > 0) {
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
            move_relative_position(wheels.frontLeft, frontLeftSpeed, (frontLeftSpeed < 0) ? -distance : distance);
            move_relative_position(wheels.frontRight, frontRightSpeed, (frontRightSpeed < 0) ? -distance : distance);
            move_relative_position(wheels.backLeft, rearLeftSpeed, (rearLeftSpeed < 0) ? -distance : distance);
            move_relative_position(wheels.backRight, rearRightSpeed, (rearRightSpeed < 0) ? -distance : distance);
            while (get_motor_done(wheels.frontLeft) == 0 && get_motor_done(wheels.frontRight) == 0 && get_motor_done(wheels.backLeft) == 0 && get_motor_done(wheels.backRight) == 0) {
                msleep(10);
            }
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

/* Here's the idea
Get the initial params
Get the final params
Have the robot slowly phase from the initial to final params
Throw in a slow rotation at the same time
Be sure to ratio!
*/

void tapeDetection(const char *params) {
    int speed, direction;
    if (sscanf(params, "%d %d", &speed, &direction) == 2) {
        alignRotation(direction, speed);
    }
    else {
        printf("Wrong amount of things dumbass!");
    }
    return;
}