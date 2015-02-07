#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	//%%% Vocabulary and definitions - if you don't know a word it will most likley be here
	//NCIU = Not Currently In Use (will be taken out in optimized code, however for ease of reading and understanding structure they are in)
	//Pointers: The little asterisk *, don't concern yoursself about this to much unless you are a coder in which case just Google it
	//Autonomous: The start of the game, where the robot runs pre-determined commands and there is no user control
	//Teleoperation: The time of the game where drivers step forward and take control of the robot
	//Deadzone: A space where there may be input, but nothing will be activated to make sure it wasn't by accident
	CANTalon *TalonSRX1;
	CANTalon *TalonSRX2;
	CANTalon *TalonSRX3;
	CANTalon *TalonSRX4;

	RobotDrive *DriveSystem; //NCIU

	Joystick *LeftStick; //Left and Right sticks are for driving
	float LeftStickInput = 0.0;
	Joystick *RightStick;
	float RightStickInput = 0.0;
	Joystick *XBoxPlayer1; //Controller of basically anything that isn't drive
	//XBox Controller Buttons
	//A = 1    B = 2  X = 3   Y = 4  LB = 5  RB = 6  Back = 7  Start = 8  LeftTrigger Click = 9  RightTrigger Click = 10
	//XBox Controller Axis
	//Leftstick X = 0  Leftstick Y = 1  Left Trigger = 2  Right Trigger = 3  Right X = 4  Right Y = 5
	float LeftXBoxXInput = 0.0; //NCIU
	float LeftXboxYInput = 0.0; //NCIU
	float XBoxLeftTrigger = 0.0; //NCIU
	float XBoxRightTrigger = 0.0; //NCIU
	float RightXBoxXInput = 0.0; //NCIU
	float RightXboxYInput = 0.0; //NCIU

	Talon *LiftMotor;
	bool MotorForward = false;
	bool MotorReverse = false; //NCIU

	DigitalInput *LimitSwitchTop;
	bool LimitSwitchTopCheck = false; //NCIU
	DigitalInput *LimitSwitchBot; //NCIU
	bool LimitSwitchBotCheck = false; //NCIU

	DoubleSolenoid *ArmSolenoid;
	bool SolenoidForward = false;
	bool SolenoidReverse = false;
	bool SolenoidOff = false; // NCIU

	void RobotInit()
	{
		//When the robot becomes activated it will initialize, acepting the pointers%%% from above and finding out what they are
		TalonSRX1 = new CANTalon(1);
		TalonSRX2 = new CANTalon(2);
		TalonSRX3 = new CANTalon(3);
		TalonSRX4 = new CANTalon(4);

		DriveSystem = new RobotDrive(TalonSRX1, TalonSRX2, TalonSRX3, TalonSRX4); //Keeping this in just in case we suddenly need it

		LeftStick = new Joystick(0);
		RightStick = new Joystick(1);
		XBoxPlayer1 = new Joystick(0);

		LiftMotor = new Talon(0);

		LimitSwitchTop = new DigitalInput(0);
		LimitSwitchBot = new DigitalInput(1);

		ArmSolenoid = new DoubleSolenoid(5, 3, 4);
	} //End RobotInit

	void AutonomousInit()
	{
		//Called at the start of Autonomous%%%
		//If you want to initialize any variables for Autonomous put them here
	} //End AutonomousInit

	void AutonomousPeriodic()
	{
		//Called periodicly during Autonomous
	} //End AutonomousPeriodic

	void TeleopInit()
	{
		//Called at the start of Teloperation%%%
		//If you want to initialize any variables for Teleoperation put them here
	} //End TeleopInit

	void TeleopPeriodic()
	{
		//Called periodicly during Teleoperation
								/*	Tank drive system based on the Y input of each joystick		*/
		LeftStickInput = LeftStick->GetY();
		RightStickInput = RightStick->GetY();

		TalonSRX1->Set(LeftStickInput);
		TalonSRX2->Set(LeftStickInput);
		TalonSRX3->Set(RightStickInput);
		TalonSRX4->Set(RightStickInput);
//////////////////////////////////////////////////LIFT MOTOR AND LIMIT SWITCH////////////////////////////////////////////////////////////////
		if (XBoxPlayer1->GetRawAxis(3) < -.2 or XBoxPlayer1->GetRawAxis(3) > .2)
		{
			if (MotorForward == false) //If bool is false
			{
				MotorForward = true; //Set it to true
				if (LimitSwitchTop->Get() != true) //If LimitSwitchTop is not sending a true signal
				{
					LiftMotor->Set(XBoxPlayer1->GetRawAxis(3)); //Set the lift motor to the XBoxPlayer1 righttrigger axis
				}
			}
			else //If MotorForward is not false (true)
			{
				if (LimitSwitchTop->Get() == true) //If the limit switch is activated
				{
					LiftMotor->Set(0.0); //Set the LiftMotor to 0.0 (0ff)
				}
			}
		}
		else MotorForward = false; //If LeftStick X axis is not in the above parameters set MotorForward to false

		if (XBoxPlayer1->GetRawAxis(3) >= -.2 and XBoxPlayer1->GetRawAxis(3) <= .2) //If RightTrigger is in the deadzone%%%
		{
			LiftMotor->Set(0.0); //Set it to 0.0 (off)
		}
///////////////////////////////////////////////////////////////SOLENOID//////////////////////////////////////////////////////////////////////
															//FORWARD//
		if (XBoxPlayer1->GetRawButton(1) == true) //if XBoxPlayer1 A gets activated
		{
			if (SolenoidForward == false) //If SolenoidForward is false
			{
				SolenoidForward = true; //Set it to true
				ArmSolenoid->Set(DoubleSolenoid::Value::kForward); //And set ArmSolenoid to forward
			}
		}
		else SolenoidForward = false; //If XBoxPlayer1 A is not activated set SolenoidForward to false
															//REVERSE//
		if (XBoxPlayer1->GetRawButton(2) == true) //If XBoxPlayer1 B  is activated
		{
			if (SolenoidReverse == false) //If SolenoidReverse is false
			{
				SolenoidReverse = true; //Set it to true
				ArmSolenoid->Set(DoubleSolenoid::Value::kReverse); //And set ArmSolenoid to reverse
			}
		}
		else SolenoidReverse = false; //If XBoxPlayer1 B is not activated set SolenoidReverse to false
															//Off//
		if (XBoxPlayer1->GetRawButton(1) != true and XBoxPlayer1->GetRawButton(2) != true) //If neither button is pressed
		{
			ArmSolenoid->Set(DoubleSolenoid::Value::kOff); //Set ArmSolenoid to off
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}//End TeleopPeriodic

}; //End Robot Class

START_ROBOT_CLASS(Robot); //Starts the class Robot (see the top of the page, that is what we are starting and thefore it starts everything
