#ifndef TRANSLATION_H
#define TRANSLATION_H

/* ----- Translational Movement ----- */
void forwardDrive(int units, int speed);
void backwardDrive(int units, int speed);
void rightDrive(int units, int speed);
void angleDrive(int distance, int degrees, int speed);
void rotationalDrive(int distance, int directionsRadians, int turningRadians, int rotationalSpeed, int translationalSpeed);
void rotate(int degrees, int speed);
void stop(int motorSpeed);
void centerDrive(int targetDistance, int baseSpeed, int kp);

/* ----- Servo Movement ------- */

void servoPosition(int port, int position, int iterations);
void openClaw();
void closeClaw(int position);
void verticalArm();

void startUp();

#endif // TRANSLATION_H