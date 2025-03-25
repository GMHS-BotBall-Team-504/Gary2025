#ifndef TRANSLATION_H
#define TRANSLATION_H

/* ----- Translational Movement ----- */
void forwardDrive(int units, int speed);
void rotate(int degrees, int speed);
void stop();

/* ----- Servo Movement ------- */

void servoPosition(int port, int position, int iterations);


void startUp();
void *servoThread(void *dataPtr); 

#endif // TRANSLATION_H