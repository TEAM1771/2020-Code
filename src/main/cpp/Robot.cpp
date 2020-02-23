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

  static bool isShooting = false;
  if(lStick.GetTrigger())
  {
    hopper.feedShooter();
    isShooting = true;
  }
  else if (isShooting)
  {
    isShooting = false;
    hopper.stopFeed();
  }
  else
  {
    hopper.controlFeed();
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
