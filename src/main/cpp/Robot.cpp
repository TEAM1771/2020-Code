#include "Robot.hpp"
#include <frc/Timer.h>

void Robot::AutonomousInit()
{
    auton->init();
}

void Robot::AutonomousPeriodic() 
{
    auton->run();
}

void Robot::TeleopInit()
{
    
}

void Robot::TeleopPeriodic()
{
    
}

void Robot::TestPeriodic()
{
    
}

void Robot::DisabledInit()
{

}

void Robot::DisabledPeriodic()
{
    
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
