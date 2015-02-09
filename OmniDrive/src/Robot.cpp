#include "WPILib.h"

class Robot: public IterativeRobot
{

private:
	CANTalon *talonsrx1;
	CANTalon *talonsrx2;
	CANTalon *talonsrx3;
	CANTalon *talonsrx4;
	RobotDrive *omnidrive;
	Joystick *leftstick;
	Joystick *rightstick;

	//////////////////////////////////////////MAGIC STUFF FOR MECANUM DRIVE///////////////////////////////////////////////
	//w is to ensure originality and definetly isn't my initial
	double wspeed = leftstick->GetY();
	double wdirection = rightstick->GetY();
	double wrotation = rightstick->GetX();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void RobotInit()
	{
	talonsrx1 = new CANTalon(1);
	talonsrx2 = new CANTalon(2);
	talonsrx3 = new CANTalon(3);
	talonsrx4 = new CANTalon(4);
	omnidrive = new RobotDrive (talonsrx1, talonsrx2, talonsrx3, talonsrx4);
	leftstick = new Joystick(0);
	rightstick = new Joystick(1);
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
	omnidrive->MecanumDrive_Cartesian(wspeed, wdirection, wrotation);

	/*if (leftstick->GetRawButton(3))
	{
	talonsrx1->Set(wrotation);
	talonsrx2->Set(wrotation);
	talonsrx3->Set(-(wrotation));
	talonsrx4->Set(-(wrotation));
	}*/

	}

	void TestPeriodic()
	{
	//empty
	}
};

START_ROBOT_CLASS(Robot);
