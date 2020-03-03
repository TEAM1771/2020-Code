#include "Robot.hpp"
#include <frc/Timer.h>

Robot::Robot()
{
    activeIntake = false;
}

void Robot::AutonomousInit()
{

}

//Simple Auton should drive forward while aiming back, and then shooting.
void Robot::SimpleAuton()
{
    static bool readyToAim = false;

    static frc::Timer autonDriveTimer; //Used to track how long to drive for
    static frc::Timer autonShootTimer; //Used to track when we can shoot (basically waiting for spin up to complete)
    static frc::Timer autonFeedTimer;


    static bool autonInit = true; //First loop initilization
    if(autonInit)
    {
        
        autonDriveTimer.Stop();
        autonDriveTimer.Reset();
        autonDriveTimer.Start();

        autonShootTimer.Stop();
        autonShootTimer.Reset();
        autonShootTimer.Start();

        autonFeedTimer.Stop();
        autonFeedTimer.Reset();

        autonInit = false;
    }
    turret.limelight_led(true);
    turret.bangbangControl();

    bool const driving = autonDriveTimer.Get() < AUTON::AUTON_DRIVE_TIMER;
    bool const shootWheelReady = autonShootTimer.Get() < AUTON::AUTON_SHOOT_TIMER;
    bool const not_done = autonFeedTimer.Get() < AUTON::AUTON_FEED_SHOOTER_TIMER;
   
   if (driving)
   {
       intake.deploy(true);
       drive.drive(-.2,-.2);
   }
   else
   {
       drive.drive(0,0);
   }

   if(shootWheelReady && not_done)
   {
        if (turret.getTurnyTurnyValue() > SHOOTER::TURRET::BACKWARDS - 2 
             && turret.getTurnyTurnyValue() < SHOOTER::TURRET::BACKWARDS + 2 )
        {
            readyToAim = true;
        }
        else if(!readyToAim)
        {
            turret.aimRightPID();
        }

        if(readyToAim && not_done)
        {
            if( turret.aimWithCameraLimelight() < .05 )
            {
                static bool startedShooting = false;
                if(!startedShooting)
                {
                    autonFeedTimer.Start();
                    startedShooting = true;
                }
                else 
                {
                    hopper.feedShooter();
                }
            }
        }
   }
   else if (not_done)
   {
        turret.aimRightPID();
   }
   else
   {
       turret.aimZero();
       turret.zeroHood();
   }


}

void Robot::AutonomousPeriodic() 
{
    SimpleAuton();
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
    //hopper.manualIndexerControl(lStick.GetY());
//hopper.manualTransportControl(rStick.GetY());
    //TurretManager();
    IntakeManager();

    turret.limelight_led(true);
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
    turret.getCameraData();
    //frc::SmartDashboard::PutNumber("Y Value", turret.getCameraY());
    double valueToReturn = frc::SmartDashboard::GetNumber("Hood Pos", 0);
        
    if(valueToReturn < SHOOTER::HOOD::SAFE_TO_TURN)
        valueToReturn = SHOOTER::HOOD::SAFE_TO_TURN;
    else if (valueToReturn > SHOOTER::HOOD::TRAVERSE)
        valueToReturn = SHOOTER::HOOD::TRAVERSE;
    
    //std::cout << oStick.GetThrottle() << '\n';
    double hood = turret.scaleOutput(-1,1, SHOOTER::HOOD::TRAVERSE,SHOOTER::HOOD::SAFE_TO_TURN, -oStick.GetThrottle());
    //if(oStick.GetThrottle() > 0)
      //  turret.maintainRPM();
    std::cout << "hood " << hood << '\n';
    std::cout << "yval: " << turret.getCameraY() << '\n';
    
    // if(lStick.GetThrottle() > 0)
        turret.bangbangControl();
    turret.debugSetHoodAngle(hood);
}

void Robot::TurretManager()
{
        static bool aiming = false;
        static bool isCommandingHood = false;
            
        turret.bangbangControl(); 
        if (oStick.GetRawButton(BUTTONS::TURRET::AIM_LEFT))
        {
            if (!aiming)
            {
                turret.aimLeftPID();
                turret.traverseHood();

                if ( turret.getTurnyTurnyValue() > SHOOTER::TURRET::FORWARD - 2 
                  && turret.getTurnyTurnyValue() < SHOOTER::TURRET::FORWARD + 2 )
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
                isCommandingHood = true;
                turret.limelight_led(true);
            }
        }
        else if(oStick.GetRawButton(BUTTONS::TURRET::AIM_RIGHT))
        {
            turret.bangbangControl();
            if (!aiming)
            {
                turret.aimRightPID();
                turret.traverseHood();

                if ( turret.getTurnyTurnyValue() > SHOOTER::TURRET::BACKWARDS - 2 
                  && turret.getTurnyTurnyValue() < SHOOTER::TURRET::BACKWARDS + 2 )
                {
                    aiming = true;
                    turret.limelight_led(true);
                }
            }
            else
            {
                turret.aimWithCameraLimelight();
            }
            intake.deploy(true);
            activeIntake = true;
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
            turret.limelight_led(false);
            turret.zeroHood();
            //turret.stopShooter();
            activeIntake = false;
            isCommandingHood = false;
        }
        

        // if(oStick.GetRawButtonReleased(BUTTONS::TURRET::AIM_CAMERA) )
        // {
        //     turret.stopAiming(); 
        // }
    

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

void Robot::ClimberManager()
{
    if(lStick.GetRawButton(BUTTONS::CLIMBER::RAISE))
        climber.climb(true);
    else climber.climb(false);
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
