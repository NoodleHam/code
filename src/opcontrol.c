#include <API.h>
#include "ports.h"
#include "basicMovement.h"
#include "advancedMovement.h"
#include "sensors.h"
#include "controller.h"


extern Gyro gyro;


void operatorControl()
{
	//Mode 0: Tank Drive
	int mode = 0;

	if(mode == 0)
	{
		//startLoops();
		while (1)
		{
			drive();
			runFlipper();
			delay(100);
		}
		//stopLoops();
	}

	if(mode == 1)
	{
		if(joystickGetDigital(MAIN_JOYSTICK, 8, JOY_RIGHT))
		{
			imeInitializeAll();
			resetEncoderSteps(1);
			setMotors(127,127);
			wait(1000);
			setMotors(0,0);
			double distanceTraveled = (getEncoderSteps(1) / 627.2) * 4;
			printf("%.2f", distanceTraveled);
		}
	}
}
