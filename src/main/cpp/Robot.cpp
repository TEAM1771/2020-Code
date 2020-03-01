#include "Robot.hpp"

Robot::Robot()
{
  activeIntake = false;
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
  if(oStick.GetRawButton(BUTTONS::HOPPER::SHOOT))
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
  TurretManager();
  IntakeManager();

  
}

void Robot::TurretManager()
{
    static bool aiming = false;
    static bool isCommandingHood = false;
      
    if (oStick.GetRawButton(BUTTONS::TURRET::AIM_LEFT))
    {
      turret.bangbangControl(); 
      if (!aiming)
      {
        turret.aimLeftPID();
        if ( turret.getTurnyTurnyValue() > SHOOTER::TURRET::FORWARD-2 && turret.getTurnyTurnyValue() < SHOOTER::TURRET::FORWARD+2)
        {
          aiming = true;
        }
      }
      else{
        turret.aimWithCameraLimelight();
      }
      intake.deploy(true);
      activeIntake = true;
      if( !isCommandingHood)
      {
        turret.traverseHood();
        isCommandingHood = true;
      }
    }
    else if(oStick.GetRawButton(BUTTONS::TURRET::AIM_RIGHT))
    {
      turret.bangbangControl();
      if (!aiming)
      {
        turret.aimRightPID();
        if ( turret.getTurnyTurnyValue() > SHOOTER::TURRET::BACKWARDS-2 && turret.getTurnyTurnyValue() < SHOOTER::TURRET::BACKWARDS+2)
        {
          aiming = true;
        }
      }
      else{
        turret.aimWithCameraLimelight();
      }
      intake.deploy(true);
      activeIntake = true;
      if( !isCommandingHood)
      {
      turret.traverseHood();
      isCommandingHood = true;
      }
      
    }
    else if(oStick.GetRawButton(BUTTONS::TURRET::TURRET_HOOD_BATTERSHOT))
    {

        //turret.traverseHood();
        turret.bangbangControl();
        turret.aimLeftPID();
        intake.deploy(true);
        activeIntake = true;
        if(!isCommandingHood)
        {
          turret.traverseHood();
          isCommandingHood = true;
        
        }
        if(turret.getTurnyTurnyValue() < SHOOTER::TURRET::SAFE_TO_DEPLOY_HOOD_FRONT)
        {
          turret.batterHood();  
        }
        else
        {
          turret.traverseHood();
        }
    }
    /*else if (oStick.GetRawButton(BUTTONS::TURRET::AIM_RIGHT_MANUAL))
    {
      turret.aimRight();
    }
    else if (oStick.GetRawButton(BUTTONS::TURRET::AIM_LEFT_MANUAL))
    {
      turret.aimLeft();
    }*/
   /* else if(oStick.GetRawButton(BUTTONS::TURRET::AIM_CAMERA))
    {
      turret.bangbangControl();
      turret.aimWithCameraLimelight();
    }
    */
    else
    {
      if(turret.getHoodValue() > SHOOTER::HOOD::SAFE_TO_TURN)
      {
        turret.aimZero();
      }
      aiming = false;
      turret.zeroHood();
      turret.stopShooter();
      activeIntake = false;
      isCommandingHood = false;
    }
    

    if(oStick.GetRawButtonReleased(BUTTONS::TURRET::AIM_CAMERA) )
    {
    turret.stopAiming(); 
    }
  

 //turret.bangbangControl();
 //
 // turret.maintainRPM();  
  /*if(oStick.GetY() >= 0){
  turret.rpmWithStick(0);
  }
  else
  {
  turret.rpmWithStick(oStick.GetY());
  }*/
  //std::cout << oStick.GetY() << std::endl;

  turret.giveStatus();

}


void Robot::IntakeManager()
{
  // Intake down

  if(!activeIntake){
  intake.deploy(oStick.GetRawButton(BUTTONS::INTAKE::intakedown));  
  }

  
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
