# Recycle-Rush-Robot-Code
Team 3926's code for Recycle Rush
<<<<<<< HEAD
Versial 1.3 (Final)

<h3>This project contains the code for team 3926's iterative-based robot. Features on this robot are as follows. </h3>
<OL>
<LI> Tank drive base driven by 4 motors connected to Talon SRXs (2 for each side)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Basic Mode: Driven by two joysticks, as tank drive normally is<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Safe Mode: Press the left stick trigger to divide the input to the joysticks by 2<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Straight Mode: Press the right stick trigger to set the left sticks input equal to that of the right's, making the robot drive perfectly straight (can be used alongside Safe Mode)<br>
<LI> A lift system with connected arms for lifting totes<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Controlled by a boolean and counter system press the button once to start an action press it again to stop it<br>
<LI> A pneumatic syllander attached to the arms for gripping totes<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Controlled by a boolean and counter system press the button once to start an action press it again to stop it<br>
</OL>
=======
THIS IS NOT A FINISHED PRODUCT BY ANY MEANS! PLEASE TREAT IT AS SUCH!

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

So I (Wilke) Don't go insane with comments in code

- %%% Vocabulary and definitions. If you don't know a word it will most likley be here
- NCIU (Not currently in use (will be taken out in optimized code, however for ease of reading and understanding structure they are in))
- Pointers: The little asterisk, don't concern yourself about this to much unless you are a coder in which case just use google.
- Autonomus: the start of the game, where the robot runs pre-determined commands and there is no user control
- Teleoperation: the time of the game where drivers step forward and take control of the robot
- Deadzone: A space where there may be input, but nothing will be activated to make sure it wasn't by accident

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

XBox Controller Buttons
	A = 1    B = 2  X = 3   Y = 4  LB = 5  RB = 6  Back = 7  Start = 8  LeftTrigger Click = 9  RightTrigger Click = 10
	XBox Controller Axis
	Leftstick X = 0  Leftstick Y = 1  Left Trigger = 2  Right Trigger = 3  Right X = 4  Right Y = 5

///////////////////////////////////////////////TANK BASE////////////////////////////////////////////////////////////////////////////

LeftStick, RightStick = Drive Sticks
xStick1 = Arm CIM. (UP and DOWN)
>>>>>>> parent of fdd269a... Merge remote-tracking branch 'origin/master'
