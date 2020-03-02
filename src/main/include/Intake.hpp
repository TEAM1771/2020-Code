/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/livewindow/LiveWindow.h>
#include <rev/CANSparkMax.h>
#include "Constants.hpp"
#include <frc/Solenoid.h>

class Intake
{

    frc::Solenoid intakeair {INTAKE::intakeairport};
    bool intakeDeployed = false;
public:
    rev::CANSparkMax intakeneo {INTAKE::IntakePort, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    Intake();
    void deploy(bool val);
    bool isIntakeDown();

};