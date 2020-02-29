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
  if(BUTTONS::HOPPER::SHOOT)
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
  TurretManager();
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

  if (oStick.GetRawButton(BUTTONS::TURRET::AIM_LEFT))
  {
   turret.aimLeftPID();
  }
  else if(oStick.GetRawButton(BUTTONS::TURRET::AIM_RIGHT))
  {
   turret.aimRightPID();
  }
  else if (oStick.GetRawButton(BUTTONS::TURRET::AIM_RIGHT_MANUAL))
  {
    turret.aimRight();
  }
  else if (oStick.GetRawButton(BUTTONS::TURRET::AIM_LEFT_MANUAL))
  {
    turret.aimLeft();
  }
  else if(oStick.GetRawButton(BUTTONS::TURRET::AIM_CAMERA))
  {
    turret.aimWithCamera();
  }

  if( oStick.GetRawButtonReleased(BUTTONS::TURRET::AIM_RIGHT_MANUAL) 
    || oStick.GetRawButtonReleased(BUTTONS::TURRET::AIM_LEFT_MANUAL) 
    || oStick.GetRawButtonReleased(BUTTONS::TURRET::AIM_CAMERA) )
  {
   turret.stopAiming(); 
  }

 turret.bangbangControl();
 //
 // turret.maintainRPM();  
  /*if(oStick.GetY() >= 0){
  turret.rpmWithStick(0);
  }
  else
  {
  turret.rpmWithStick(oStick.GetY());
  }*/
  std::cout << oStick.GetY() << std::endl;

  turret.giveStatus();

}

void Robot::IntakeManager()
{
  // Intake down

  intake.deploy(oStick.GetRawButton(BUTTONS::INTAKE::intakedown));
  
  if (oStick.GetRawButton(BUTTONS::INTAKE::intakein))
    {// Intake in
    intake.intakeneo.Set(1);
    }
  else if (oStick.GetRawButton(BUTTONS::INTAKE::intakeout))
    {// Intake out 
    intake.intakeneo.Set(-1);
    }
  else
    {//Idle 
    intake.intakeneo.Set(0);
    }

}

void Robot::DisabledInit()
{

}

void Robot::DisabledPeriodic()
{
  turret.giveStatus();
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
