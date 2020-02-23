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
  hopper.controlFeed();
  if(lStick.GetTrigger())
  {
    hopper.feedShooter();
  }
  else
  {
    hopper.stopFeed();
  }
  
}

void Robot::TestPeriodic()
{
  hopper.manualIndexerControl(lStick.GetY());
  hopper.manualTransportControl(rStick.GetY());
  
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
