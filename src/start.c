
#include <stdio.h>
#include <stdlib.h>

#define RESET_COLOR "\033[0m"
#define GREEN_COLOR "\033[32m"
#define RED_COLOR "\033[31m"
#define YELLOW_COLOR "\033[33m"
#define CYAN_COLOR "\033[36m"

void display_menu() {
    system("clear");
    printf(CYAN_COLOR "==============================================================\n");
    printf("   " GREEN_COLOR "██████╗  ██████╗ ████████╗██████╗  █████╗ ██╗     ██╗     \n");
    printf("   ██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗██╔══██╗██║     ██║     \n");
    printf("   ██████╔╝██║   ██║   ██║   ██████╔╝███████║██║     ██║     \n");
    printf("   ██╔══██╗██║   ██║   ██║   ██╔══██╗██╔══██║██║     ██║     \n");
    printf("   ██████╔╝╚██████╔╝   ██║   ██████╔╝██║  ██║███████╗███████╗\n");
    printf("   ╚═════╝  ╚═════╝    ╚═╝   ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝\n" RESET_COLOR);
    printf(CYAN_COLOR "==============================================================\n");
    printf("                    Select an option:\n");
    printf(CYAN_COLOR "==============================================================\n");
    printf("|     1. Run manual.c       |        2. Run main.c           |\n");
    printf("|     3. Run auto.c         |        4. Exit                 |\n");
    printf(CYAN_COLOR "==============================================================\n");
    printf("\n");
}

int get_choice() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}


int main() {
    display_menu();
    int choice = get_choice();
    switch (choice) {
        case 1:
            system("./manual");
            break;
        case 2:
            system("./main");
            break;
        case 3:
            system("./auto");
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
    }
}