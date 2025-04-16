#include "../include/library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define TAPE_THRESHOLD 1500
#define DEGREES_TO_TICKS 9.013888889
#define STRAFE_CM_TO_TICKS 143.614670791
#define STRAIGHT_CM_TO_TICKS 130.0000

#define RESET_COLOR "\033[0m"
#define GREEN_COLOR "\033[32m"
#define RED_COLOR "\033[31m"
#define YELLOW_COLOR "\033[33m"
#define CYAN_COLOR "\033[36m"

// Function prototypes
void executeCommand(const char *command, const char *params);
void displayMenu();
void executeBlock(int blockNumber);

// Predefined command blocks
const char *commandBlocks[][5] = {
    {"driveForward 100", "turnRight 90", "driveForward 50", NULL},
    {"driveBackward 50", "turnLeft 45", "driveForward 75", NULL},
    {"lowerArm", "strafePos", "pvcPos", "openPos", NULL}
};

int main() {
    int choice;

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
    printf(CYAN_COLOR "   Select a block of commands to execute\n");
    printf("==============================================================\n" RESET_COLOR);

    while (1) {
        displayMenu();
        printf(YELLOW_COLOR "\n[SELECT BLOCK]> " RESET_COLOR);
        if (scanf("%d", &choice) != 1 || choice == 0) {
            printf(GREEN_COLOR "\nExiting Autonomous Mode. Goodbye!\n" RESET_COLOR);
            break;
        }

        if (choice > 0 && choice <= (sizeof(commandBlocks) / sizeof(commandBlocks[0]))) {
            executeBlock(choice - 1);
        } else {
            printf(RED_COLOR "Invalid choice. Please try again.\n" RESET_COLOR);
        }
    }

    return 0;
}

void displayMenu() {
    printf(CYAN_COLOR "\nAvailable Command Blocks:\n" RESET_COLOR);
    for (int i = 0; i < (sizeof(commandBlocks) / sizeof(commandBlocks[0])); i++) {
        printf(GREEN_COLOR " %d. Block %d\n" RESET_COLOR, i + 1, i + 1);
    }
    printf(GREEN_COLOR " 0. Exit\n" RESET_COLOR);
}

void executeBlock(int blockNumber) {
    printf(GREEN_COLOR "\nExecuting Block %d...\n" RESET_COLOR, blockNumber + 1);
    for (int i = 0; commandBlocks[blockNumber][i] != NULL; i++) {
        char command[50], params[50];
        if (sscanf(commandBlocks[blockNumber][i], "%s %[^\n]", command, params) < 1) {
            continue;
        }
        executeCommand(command, params);
    }
    printf(GREEN_COLOR "Block %d execution completed.\n" RESET_COLOR, blockNumber + 1);
}

void executeCommand(const char *command, const char *params) {
    // Simulate command execution (replace with actual logic if needed)
    printf(CYAN_COLOR "Executing: %s %s\n" RESET_COLOR, command, params);
}