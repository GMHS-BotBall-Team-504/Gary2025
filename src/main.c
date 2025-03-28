#include <kipr/wombat.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../include/library.h"
#define startingDirection 180

int main() {
    
    for (int i = 0; i < 4; i++) {
        move_relative_position(i, 8000, 1200);
    }
    block_motor_done(0);
    stop(1500);


    printf("hello");
    startUp();

    return 0;

}