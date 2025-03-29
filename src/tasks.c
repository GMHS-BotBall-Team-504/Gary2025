#include "../include/tasks.h"
#include "../include/translation.h"
#include "../include/positions.h"
#include "../include/ports.h"
#include <kipr/wombat.h>

void grabPom(int version) {
    if (get_servo_position(servos.elbow) != elbowPos.parallelToFloor) {
        servoPosition(servos.elbow, elbowPos.parallelToFloor, 1);
    }
    if (get_servo_position(servos.wrist) != wristPos.ground) {
        servoPosition(servos.wrist, wristPos.ground, 1);
    }
    msleep(200);
    if (version != 2) {
        forwardDrive(2000, 1500);
        servoPosition(servos.claw, clawPos.closedPoms, 1);

        // Run both the elbow, wrist, and rotation thread
        servoPosition(servos.elbow, elbowPos.PVC, 1);
        servoPosition(servos.wrist, wristPos.PVC, 1);


        servoPosition(servos.claw, clawPos.open, 1); // Drop in container

        // Reset
        
    }
    else {

    }
}

void potato() {

}