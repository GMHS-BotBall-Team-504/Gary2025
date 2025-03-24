#include "../include/translation.h"
#include "../include/ports.h"
#include "../kipr/wombat.h"

/* ----- Translational Movement ----- */

void forwardDrive(int speed) {

    stop(speed);
}

void rotate(int degrees, int speed) {

}

// Revamped version of alloff so there's less drift
void stop(int motorSpeed) {
    for (int i; i < 4; i++) {
        mav(i, (-1) * motorSpeed);
    }
    msleep(20);
    ao();
}


/* ----- Servo Movement ------- */

void servoPosition(int port, int position, int iterations) {

}


// Ran during the 1 minute before games start
void startUp() {
    alloff();
    msleep(500);
}
