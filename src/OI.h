
#ifndef SRC_OI_H_
#define SRC_OI_H_
#include "WPILib.h"
#include "XboxController.h"
#include "Components/AnalogJoystickButton.h"
#include "Components/POVJoystickButton.h"
#include "Components/Joystick1771.h"

class OI {
private:
	Joystick1771* driveStick;
	Joystick1771* operatorStick;
	//Joystick* debugStick;

	//Driver Buttons
	AnalogJoystickButton* intakeButton;
	Button* intakeRevButton;
	Button* rotateToLeftAngleCam;
	Button* rotateToRightAngleCam;
	Button* driveTrainShift;
	Button* portcullisTraverse;
	Button* stopSpinButton;

	//Operator Buttons
	AnalogJoystickButton* fireBall;
	AnalogJoystickButton* operatorRevIntake;
	Button* turnOnShooter;
	Button* turnOffShooter;
	Button* manualIntakeButton;
	Button* changeShooterAngle;
	Button* shooterRevButton;
	Button* dinkerDownButton;
	POVJoystickButton* shooterIncButton;
	POVJoystickButton* shooterDecButton;
	POVJoystickButton* cameraIncButton;
	POVJoystickButton* cameraDecButton;

	//Debug Buttons
//	Button* rotateToAngleNoCam;
//	Button* waitForBallTest;

public:
	OI();
	virtual ~OI();
	Joystick1771* GetDriveStick();
	Joystick1771* GetOperatorStick();
	//Joystick* GetDebugStick();
};

#endif /* SRC_OI_H_ */
