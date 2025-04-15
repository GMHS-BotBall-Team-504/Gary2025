#ifndef TRANSLATION_H
#define TRANSLATION_H

/* ----- Translational Movement ----- */

void frisbeeDriveWithAngle(float angle, float speed, float omega, int maxSpeed);
void angularDrive(float angle, float speed, float omega, int maxSpeed);
void crash(int backLeft, int backRight, int frontLeft, int frontRight);
void alignRotation(int direction, int ticksPerSecond);
void alignBack(int ticksPerSecond);

void forwardDrive(int units, int speed);
void backwardDrive(int units, int speed);
void rightDrive(int units, int speed);
void leftDrive(int units, int speed);
void angleDrive(int distance, int degrees, int speed);
void rotationalDrive(int distance, int directionsRadians, int turningRadians, int rotationalSpeed, int translationalSpeed);
void rotate(int degrees, int speed);
void stop(int motorSpeed);
void backStop(int motorSpeed);
void rotateStop(int motorSpeed);
void centerDrive(int targetDistance, int baseSpeed, int kp);

/* ----- Servo Movement ------- */

void strafePosition();
void servoPosition(int port, int position, int iterations);
void openClaw();
void closeClaw(int position);
void verticalArm();

void startUp();

#endif // TRANSLATION_H