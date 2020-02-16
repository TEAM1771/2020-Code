#include "Robot.hpp"

Robot::Robot()
{

}

void Robot::AutonomousInit()
{

}

void Robot::AutonomousPeriodic() 
{

}

void Robot::TeleopInit()
{

}

void Robot::TeleopPeriodic()
{
  drive.drive(lStick.GetY(), rStick.GetY());
  drive.shift();
}

void Robot::TestPeriodic()
{

}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
