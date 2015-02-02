#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	double safteyspeed = .3;
	double incriment = .1;
	bool triggersaftey = false;
	bool triggerincriment = false;
	bool buttonlift = false;
	bool buttonreverse = false;
	bool limitswitchactive = false;

	bool newmat1forward = false;
	bool newmat1reverse = false;
	bool newmat1off = false;
	CANTalon *talonsrx1;
	CANTalon *talonsrx2;
	CANTalon *talonsrx3;
	CANTalon *talonsrx4;

	RobotDrive *myrobot;

	Joystick *leftstick; //Joysticks have to be at 0 and 1
	Joystick *rightstick;

	Talon *liftmotor;
	DigitalInput *liftlimit;

	DoubleSolenoid *newmat1;

	void RobotInit()
	{
		talonsrx1 = new CANTalon(1); //left back
		talonsrx2 = new CANTalon(2); //left front
		talonsrx3 = new CANTalon(3); //right back
		talonsrx4 = new CANTalon(4); //right front

		myrobot = new RobotDrive (talonsrx1, talonsrx2, talonsrx3, talonsrx4);

		leftstick = new Joystick(0);
		rightstick = new Joystick(1);

		liftmotor = new Talon(0);
		liftlimit = new DigitalInput(0);

		newmat1 = new DoubleSolenoid(5, 0, 1);
	}

	void AutonomousInit()
	{
	//empty
	}

	void AutonomousPeriodic()
	{
	//empty
	}

	void TeleopInit()
	{
	//empty
	}

	void TeleopPeriodic()
	{
		myrobot->TankDrive(leftstick, rightstick);

		/*If (liftmotorIsRunning && liftLimit->Get() == true)
		{

		}*/
		if (leftstick->GetRawButton(4) == true)
		{
			if (buttonlift == false)
			{
				buttonlift = true;
				if (liftlimit->Get() != true)
				{
					//liftmotorIsRunning = true;
					liftmotor->Set(1.0);
				}
			}
			else //check to see if you hit the limit, if it was pressed and is pressed
			{
				if (liftlimit->Get() == true)
				{
					liftmotor->Set(0.0);
				}
			}
		}
		else
		{
			buttonlift = false;
		}

		if (leftstick->GetRawButton(5) == true)
		{
			if (buttonreverse == false)
			{
				buttonreverse = true;
				liftmotor->Set(-.3);
			}
			else buttonreverse = false;
		}

		else if (buttonlift == false && leftstick->GetRawButton(4) != true)
		{
		liftmotor->Set(0.0);
		}

		if (rightstick->GetRawButton(4))
		{
			if (newmat1forward == false)
			{
			newmat1forward = true;
			newmat1->Set(DoubleSolenoid::Value::kForward);
			}
		}
		else
		{
			newmat1forward = false;
		}

		if (rightstick->GetRawButton(5))
		{
			if (newmat1reverse == false)
			{
			newmat1reverse = true;
			newmat1->Set(DoubleSolenoid::Value::kReverse);
			}
		}
		else
		{
			newmat1reverse = false;
		}


	    if (newmat1forward == false && newmat1reverse == false)
		{
	    	newmat1->Set(DoubleSolenoid::Value::kOff);
		}

		Wait(0.005);
	} //end TeleopPeriodic()

	void TestPeriodic()
	{
	//empty
	}
};

START_ROBOT_CLASS(Robot);
