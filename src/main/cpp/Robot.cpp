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
  if(oStick.GetTrigger())
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
  
  IntakeManager();
}

void Robot::TestPeriodic()
{
  hopper.manualIndexerControl(lStick.GetY());
  hopper.manualTransportControl(rStick.GetY());
  IntakeManager();
  TurretManager();
  
}

void Robot::TurretManager()
{
  //Buttons need to be changed still
  //Turn Left
  if (oStick.GetRawButton(6))
  {
    turret.aimLeft();
  }
  //Turn Right
  else if(oStick.GetRawButton(7))
  {
    turret.aimRight();
  }
  //Aim with camera
  else if (oStick.GetRawButton(8))
  {
    turret.aimWithCamera();
  }
  else
  {
    turret.stopAiming();
  }
  turret.giveStatus();
  
}

void Robot::IntakeManager()
{
  // Intake down

  intake.deploy(oStick.GetRawButton(INTAKE::BUTTONS::intakedown));
  
  if (oStick.GetRawButton(INTAKE::BUTTONS::intakein))
    {// Intake in
    intake.intakeneo.Set(1);
    }
  else if (oStick.GetRawButton(INTAKE::BUTTONS::intakeout))
    {// Intake out 
    intake.intakeneo.Set(-1);
    }
  else
    {//Idle 
    intake.intakeneo.Set(0);
    }

}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
