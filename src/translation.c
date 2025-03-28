#include "../include/translation.h"
#include "../include/ports.h"
#include "../include/positions.h"
#include <kipr/wombat.h>
#include <pthread.h>
#include <stdlib.h>

/* ----- Translational Movement ----- */

void forwardDrive(int units, int speed) {
    for (int i = 0; i < 4; i++) {
        move_relative_position(i, units, speed);
    }
    block_motor_done(0);
    stop(speed);
}

void rotate(int degrees, int speed) {

}

// Revamped version of alloff so there's less drift
void stop(int motorSpeed) {
    for (int i; i < 4; i++) {
        mav(3 - i, (-1) * motorSpeed);
    }
    msleep(10);
    ao();
}

void centerDrive(int units, int speed) {
    
}

/* ----- Servo Movement ------- */

void servoPosition(int port, int position, int iterations) {
    enable_servo(port);
    float change = (float)(position - get_servo_position(port)) / iterations;
    for (int i = 0; i < iterations; i++) {
        set_servo_position(port, get_servo_position(port) + change);
        msleep(50);
    }
    while (get_servo_position(port) != position) {
        msleep(10);
    }
    disable_servo(port);

}


// Ran during the 1 minute before games start
void startUp() {
    alloff();
    disable_servos();
    msleep(500);
    servoPosition(servos.claw, clawPos.starting, 1);
    servoPosition(servos.elbow, elbowPos.starting, 1);
    servoPosition(servos.wrist, wristPos.starting, 1);
    for (int i = 0; i < 4; i++) {
        clear_motor_position_counter(i);
    }
    wait_for_light(analogPorts.underLight);
    shut_down_in(119);
}

/*
void* servoThread(void *dataPtr) {
    pthread_t newThread;
    srand(time(NULL));

    pthread_create(&newThread, NULL, servoPosition, dataPtr);

    return NULL;
}
*/