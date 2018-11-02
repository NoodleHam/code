#include "basicMovement.h"


void setSpeedLeft(int speedLeft)
{
  motorSet(MOTOR_DBL, -speedLeft);
  motorSet(MOTOR_DFL, -speedLeft);
}

void setSpeedRight(int speedRight)
{
  motorSet(MOTOR_DBR, -speedRight);
  motorSet(MOTOR_DFR, -speedRight);
}

void setMotors(int speedLeft, int speedRight)
{
  setSpeedLeft(speedLeft);
  setSpeedRight(speedRight);
}

//bool isButtonPressed()

bool isGreaterThanThreshold(int joyX, int joyY)
{
  if (abs(joyX) >= JOYSTICK_THRESHOLD || abs(joyY) >= JOYSTICK_THRESHOLD)
  {
    return true;
  }
  else
  {
    return false;
  }
}

struct controller_values getControllerValues()
{
  int stickLX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_LEFT_X);
  int stickLY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_LEFT_Y);
  int stickRX = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_X);
  int stickRY = joystickGetAnalog(MAIN_JOYSTICK, JOYSTICK_RIGHT_Y);
  struct controller_values vals;
  vals.stickLX = stickLX;
  vals.stickLY = stickLY;
  vals.stickRX = stickRX;
  vals.stickRY = stickRY;
  return vals;
}

int usePowerCurve(int joystick)
{
  int offset = FRICTION_THRESHOLD;
  if (joystick < 0)
  {
    offset = -FRICTION_THRESHOLD;
  }

  //offset is the minimum speed to start moving
  return pow(joystick/10 , 3) / 18 + offset;
}

struct controller_values remapControllerValues(struct controller_values vals)
{
  vals.stickLX = usePowerCurve(vals.stickLX);
  vals.stickLY = usePowerCurve(vals.stickLY);
  vals.stickRX = usePowerCurve(vals.stickRX);
  vals.stickRY = usePowerCurve(vals.stickRY);

  return vals;
}
