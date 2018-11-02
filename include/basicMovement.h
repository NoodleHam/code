#ifndef _BASICM_H_
#define _BASICM_H_
#include <API.h>
#include "ports.h"
#include "math.h"
#include "advancedMovement.h"

//The minimum joystick value to be perceived as intentional movement
#define JOYSTICK_THRESHOLD 15
//The minimum motor power for robot to move
#define FRICTION_THRESHOLD 10


//Set a single side of the robot a certain speed
void setSpeedLeft(int speedLeft);
void setSpeedRight(int speedRight);
//Utilize the previous methods to set each side of the robot
void setMotors(int speedLeft, int speedRight);

//bool isButtonPressed();

//Determines whether a joystick movement is intentional
bool isGreaterThanThreshold(int joyX, int joyY);
//Manipulates the joystick values by applying them to the cubic curve
// while still keeping them in range
int usePowerCurve(int input);

//Creates a storage for joystick values
struct controller_values
{
  int stickLX;
  int stickLY;
  int stickRX;
  int stickRY;
};
//Stores the joystick values for later reference
struct controller_values getControllerValues();
//Applies the cubic curve onto the stored joystick values
struct controller_values remapControllerValues(struct controller_values vals);

#endif
