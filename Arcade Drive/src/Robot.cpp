#include "WPILib.h"


class Robot: public SampleRobot
{
private:


 // DO I REALLY NEED ALL OF THIS STUFF HERE??????

	enum JOYSTICK_ID
	{
		CONTROLLER_MAIN = 1,
		CONTROLLER_SECONDARY
	};

	RobotDrive driveSystem; // robot drive system
	Joystick leftStick; // Logictech joystick 1
	Joystick rightStick; // Logictech joystick 2
	Joystick x_leftStick; //xbox Controller left Stick
	Joystick x_rightStick; //xbox Controller right Stick


public:
	Robot() :
			driveSystem(0, 1),	// initialize the RobotDrive to use motor controllers on ports 0 and 1
			leftStick(CONTROLLER_MAIN),
			rightStick(CONTROLLER_MAIN),
			x_leftStick(CONTROLLER_SECONDARY),
			x_rightStick(CONTROLLER_SECONDARY)
	{
		driveSystem.SetExpiration(0.1);
	}

	/**
	 * Runs the motors with tank steering.
	 */
	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			driveSystem.TankDrive(leftStick, rightStick); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time
		}
	}

};

START_ROBOT_CLASS(Robot);
