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

#include "Drivetrain.hpp"
<<<<<<< Updated upstream
=======
#include "Hopper.hpp"
#include "Intake.hpp"
>>>>>>> Stashed changes

class Robot : public frc::TimedRobot 
{
public:
    Robot();
    void AutonomousInit() override;
    void AutonomousPeriodic() override ;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
    
    void IntakeManager(); 
 private:
    frc::Joystick rStick { 0 },
                  lStick { 1 },
                  oStick { 2 };
    Drivetrain drive;
<<<<<<< Updated upstream
=======
    Hopper hopper;
    Intake intake;
>>>>>>> Stashed changes
    frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
};
