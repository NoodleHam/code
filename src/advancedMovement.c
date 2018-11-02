#include "advancedMovement.h"

//static TaskHandle capFlipperTask;

void moveSteps(int steps, int speed)
{
  int start = getEncoderSteps(IME_RIGHT_MOTOR);
  while (abs(getEncoderSteps(IME_RIGHT_MOTOR) - start) < steps)
  {
    setMotors(-speed, speed);
  }
  setMotors(0, 0);
}

void tankDrive(int speedLeft, int speedRight)
{
  setMotors(-speedLeft, speedRight);
}

void drive()
{
  struct controller_values controller = getControllerValues();
  struct controller_values remapped = remapControllerValues(controller);

  if(!isGreaterThanThreshold(remapped.stickLY, remapped.stickLX) &&
    !isGreaterThanThreshold(remapped.stickRY, remapped.stickRX))
  {
    setMotors(0, 0);
    return;
  }

  tankDrive(remapped.stickLY,remapped.stickRY);
  //mechanumDrive(remapped.stickLY,remapped.stickRX, remapped.stickLX);
}

void mechanumDrive(int remappedStickLeftY, int remappedStickRightX, int remappedStickLeftX)
{
  int frontLeft = remappedStickLeftY + remappedStickRightX + remappedStickLeftX;
  int backLeft = remappedStickLeftY + remappedStickRightX - remappedStickLeftX;
  int frontRight = remappedStickLeftY - remappedStickRightX - remappedStickLeftX;
  int backRight = remappedStickLeftY - remappedStickRightX + remappedStickLeftX;

  motorSet(MOTOR_DFL, frontLeft);
  motorSet(MOTOR_DBL, backLeft);
  motorSet(MOTOR_DFR, frontRight);
  motorSet(MOTOR_DBR, backRight);
}

void runFlipper()
{
  if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_UP))
  {
      motorSet(MOTOR_FLIP, -127);
  }
  else if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_DOWN))
  {
      motorSet(MOTOR_FLIP, 127);
  }
  else
  {
    motorSet(MOTOR_FLIP, 0);
  }
}

void startLoops()
{
  //capFlipperTask = taskCreate(capFlipperLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stopLoops()
{
  //taskDelete(capFlipperTask);
}

int max(int a, int b)
{
  if (a > b) {return a;}
  return b;
}

void gyroTurn(int degrees, Gyro gyro, int minSpeed)
{
  int direction;
  //postive direction means turning right (posiive degrees)
  if (degrees > 0)
  {
    direction = 1;
  }
  else
  {
    direction = -1;
  }
  degrees -= degrees / 10;
  int initial = getGyroscopeValue(gyro);
  int slowDown = 0;
  //turn while the difference is less than the target degrees
  while (abs(initial - getGyroscopeValue(gyro)) <= abs(degrees))
  {
    //if less than 38 degs to target, slow down
    int degsRemaining = abs(degrees) - abs(initial - getGyroscopeValue(gyro));
    if (degsRemaining <= 38)
    {
      //slow down by a fraction of degrees remaining;
      slowDown += degsRemaining / 3;
    }
    setMotors(max(minSpeed, GYRO_TURN_SPEED - slowDown) * direction,
      max(minSpeed, GYRO_TURN_SPEED - slowDown) * direction);
    wait(20);
  }
  setMotors(0, 0);
}
