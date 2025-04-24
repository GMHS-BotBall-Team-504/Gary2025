#include "../include/library.h"
#define TAPE_THRESHOLD 1500
#define TICKS_TO_CM 12000/51.5
#define TICKS_TO_DEG 195/180

// FORWARD TRANSLATION: y = 0.00430633x
// SIDE TRANSLATION   : y = 0.00427661x

int main() {

    wait_for_light(analogPorts.startLight);
    shut_down_in(119);

    // Strafe position, drive robot to the right up to the black line
    // Group in a thread pair
    df(1500, 50);
    strafePosition(); // Allow for strafing

    // Group in a thread pair
    dd(90, 4000, 1500);
    db(1500, 280);
    openClaw();

    // Rotate to face the poms (make sure not to lose the box)
    groundPos();
    tr(1500, 180);
    td(300, 1);
    tr(1500, 12);
    db(1500, 280);

    df(1500, 2326);
    closeClaw(); // Around the poms

    // Rotate to face the first drop-off zone
    // Group in a thread pair
    pvcPos();
    tr(1500, 95);
    turnRight(95, 1500);
    forwardDrive(950, 1500);

    openClaw(); // Drops off first pom set


    // Group in a thread pair
    strafePos();
    closeClaw();
    driveDirection(-120, unknownDistance, 1500);

    turnLeft(85, 1500); // face the poms
    leftDrive(1950, 1500); // Align left to the wall
    forwardDrive(400, 1500);
    openClaw();
    groundPos();

    driveDirection(90, 1500, 1500);
    tr(1000, 90);
    cp();

    dd(-10, 1800, 1500);
    tr(1500, 81);
    op();
    cp();

    sp();

    tl(1500, 50);
    db(1500, 500);
    td(300, -1);

    // Group in a thread pair
    strafePos();
    driveDirection(-75, unknownDistance, 1500);

    // Group in a thread pair
    turnLeft(unknownDistance, 1500); // face the poms
    groundPos();

    forwardDrive(unknownDistance, 1500); // Collect the poms
    closeClaw();

    // Group in a thread pair
    turnRight(unknownDistance, 1500); // face the third box
    pvcPos();

    forwardDrive(unknownDistance, 1500); // Above third box
    openClaw(); // drop off


    // Group in a thread pair
    strafePos();
    leftDrive(unknownDistance, 1500); // Align over the vertical tape w potato

    turnRight(180, 1500); // face the potato
    forwardDrive(unknownDistance, 1500); // Make sure to hit horizontal tape here for positioning


}


