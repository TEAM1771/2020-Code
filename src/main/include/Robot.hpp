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
#include <frc/smartdashboard/smartdashboard.h>

#include <memory>

#include "AutoFiveBall.hpp"

#include "Drivetrain.hpp"
#include "Limelight.hpp"
#include "AutoBase.hpp"
#include "Hood.hpp"
#include "Hopper.hpp"
#include "Turret.hpp"
#include "Climber.hpp"
#include "Intake.hpp"

class Robot : public frc::TimedRobot 
{
public:
    void AutonomousInit() override;
    void AutonomousPeriodic() override;

    void TeleopInit() override;
    void TeleopPeriodic() override;

    void DisabledInit() override;
    void DisabledPeriodic() override;

    void TestPeriodic() override;
    
 private:
    frc::Joystick rStick { 0 },
                  lStick { 1 },
                  oStick { 2 };

    friend class AutoFiveBall<Robot>; // Repeat this for all Auton Modes
    std::unique_ptr<AutoBase<Robot>> auton { new AutoFiveBall<Robot>(this) }; // setup active auton

    Drivetrain drivetrain;

    LimeLight limelight;
    Hood hood { limelight };
    Turret turret { limelight };
    Hopper hopper;
    Climber climber;
    Intake intake;

    frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
};
