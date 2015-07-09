#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	CANTalon *TalonSRX1;
	CANTalon *TalonSRX2;
	CANTalon *TalonSRX3;
	CANTalon *TalonSRX4;

	RobotDrive *DriveSystem;

	Joystick *LeftStick;
	float LeftStickInput = 0.0;
	Joystick *RightStick;
	float RightStickInput = 0.0;
	Joystick *XBoxPlayer1;

	Talon *LiftMotor;
	bool Button5_up_Check = false;
	int Button5_Counter = 0;
	bool Button6_down_Check = false;
	int Button6_Counter = 0;

	bool LiftSystem_Check = false;

	DoubleSolenoid *ArmSolenoid;
	bool Button1_open_Check = false;
	int Button1_Counter = 0;
	bool Button2_close_Check = false;
	int Button2_Counter = 0;

	bool PneumaticSystem_Check = false;

	void RobotInit()
	{
		TalonSRX1 = new CANTalon(1);
		TalonSRX2 = new CANTalon(2);
		TalonSRX3 = new CANTalon(3);
		TalonSRX4 = new CANTalon(4);

		DriveSystem = new RobotDrive(TalonSRX1, TalonSRX2, TalonSRX3, TalonSRX4);

		LeftStick = new Joystick(0);
		RightStick = new Joystick(1);
		XBoxPlayer1 = new Joystick(2);

		LiftMotor = new Talon(0);

		ArmSolenoid = new DoubleSolenoid(5, 7, 6);
	} //End RobotInit

	void AutonomousInit()
	{
		//Empty
	} //End AutonomousInit

	void AutonomousPeriodic()
	{
		//Empty
	} //End AutonomousPeriodic
	void TeleopInit()
	{
		//Empty
	} //End TeleopInit

	void TeleopPeriodic()
	{
	//Stick Checks
		//Lift System
		if (XBoxPlayer1->GetRawButton(5)) ++Button5_Counter; //When the button if pressed, add one to the counter
		if (Button5_Counter == 1) Button5_up_Check = true; //If the button has been hit once, set to true
		else if (Button5_Counter == 2) { //If the button has been hit twice, set to false and reset the counter
			Button5_up_Check = false;
			Button5_Counter = 0;
		}

		if (XBoxPlayer1->GetRawButton(6)) ++Button6_Counter;
		if (Button6_Counter == 1) Button6_down_Check = true;
		else if (Button6_Counter == 2) {
			Button6_down_Check = false;
			Button6_Counter = 0;
		}

		if (Button5_up_Check == false && Button6_down_Check == false) LiftSystem_Check = true;
		else LiftSystem_Check = false;

		//Pneumatic System
		if (XBoxPlayer1->GetRawButton(1)) ++Button1_Counter;
		if (Button1_Counter == 1) Button1_open_Check = true;
		else if (Button_1_Counter == 2) {
			Button1_open_Check = false;
			Button1_Counter = 0;
		}

		if (XBoxPlayer1->GetRawButton(2)) ++Button2_Counter;
		if (Button2_Counter == 1) Button2_close_Check = true;
		else if (Button2_Counter == 2) {
			Button2_close_Check = false;
			Button2_Counter = 0;
		}

		if (Button1_open_Check == false && Button2_close_Check == false) PneumaticSystem_Check = true;
		else PneumaticSystem_Check = false;

	//Saftey Codes
		DriveSystem->SetSafetyEnabled(false);
	//Drive Codes
		LeftStickInput = LeftStick->GetY();
		RightStickInput = RightStick->GetY();

		LeftStickInput = LeftStickInput * -0.5;
		RightStickInput = RightStickInput * -0.5;

		if (RightStick->GetRawButton(1) == true)
		{
			LeftStickInput = RightStick->GetY();
		}
		if (LeftStick->GetRawButton(1) == true)
		{
			LeftStickInput = LeftStickInput / 2;
			RightStickInput = RightStickInput / 2;
		}

		DriveSystem->TankDrive(LeftStickInput, RightStickInput, false);

	//Lift Code
		if(Button5_up_Check == true) LiftMotor->Set(-1);
		if(Button6_down_Check == true) LiftMotor->Set(1);
		if(LiftSystem_Check == true) LiftMotor->Set(0.0);

	//Solenoid Code
		if (Button1_open_Check == true) ArmSolenoid->Set(DoubleSolenoid::Value::kForward);
		if (Button2_close_Check == true) ArmSolenoid->Set(DoubleSolenoid::Value::kReverse);
		if (PneumaticSystem_Check == true) ArmSolenoid->Set(DoubleSolenoid::Value::kOff);
		Wait(0.005);
	}//End TeleopPeriodic


}; //End Robot Class

START_ROBOT_CLASS(Robot);
