#ifndef TRANSLATION_H
#define TRANSLATION_H

/* ----- Translational Movement ----- */
void forwardDrive(int units, int speed);
void rotate(int degrees, int speed);
void stop(int motorSpeed);
void centerDrive(int units, int speed);

/* ----- Servo Movement ------- */

void servoPosition(int port, int position, int iterations);


void startUp();

#endif // TRANSLATION_H