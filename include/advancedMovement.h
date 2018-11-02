#ifndef _ADVANCED_MOVEMENT_H_
#define _ADVANCED_MOVEMENT_H_

#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "sensors.h"
#include "controller.h"
#include "math.h"

#define MAX_DRIVE_SPEED 60
#define GYRO_TURN_SPEED 60
#define GYRO_TURN_SPEED_MIN 28
#define GYRO_TURN_SPEED_MIN_FAST 40

//Moves the robot a set distance at a set speed
void moveSteps(int steps, int speed);

void tankDrive(int speedLeft, int speedRight);

//Main drive code
void drive();

void mechanumDrive(int remappedStickLeftY, int remappedStickRightX, int remappedStickLeftX);

void runFlipper();

//Creates a constant loop for the cap flipper so that the user can turn and flip at the same time
void capFlipperLoop(void * parameter);

//Begins the loops
void startLoops();
//Ends the loops
void stopLoops();

//Returns the bigger integer of a and b
int max(int a, int b);
//Turns the robot a set number of degrees at the designated speed, slowing
//down the robot when it approaches the designated angle for increased accuracy
void gyroTurn(int degrees, Gyro gyro, int minSpeed);

#endif
