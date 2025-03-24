#ifndef TRANSLATION_H
#define TRANSLATION_H

/* ----- Translational Movement ----- */
void forwardDrive();
void rotate(int degrees, int speed);
void stop();

/* ----- Servo Movement ------- */

void servoPosition(int port, int position, int iterations);


void startUp();

#endif // TRANSLATION_H