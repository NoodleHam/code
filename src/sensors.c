#include "sensors.h"


int getEncoderSteps(int side)
{
    // Get IME tick count in the "counts" variable
    // (conversion to rotations varies depending on the motor type in use)
    int counts = 0;
    // Or if #define was used:
    imeGet(side, &counts);
    return counts;
}

void resetEncoderSteps(int side)
{
  // Reset IME to zero
  imeReset(side);
}

// Returns the value of the gyroscope in degrees
int getGyroscopeValue(Gyro gyro)
{
  return gyroGet(gyro);
}

// Sets the gyroscope value to zero
void resetGyroscopeValue(Gyro gyro)
{
  gyroReset(gyro);
}

// Returns the value of the potentiometer
int getRawPot(int port)
{
  return analogRead(port);
}
