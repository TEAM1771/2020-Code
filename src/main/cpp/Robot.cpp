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


    static bool doneDriving = false;
    static bool readyToAim = false;
    static bool readyToTrack = false;
    static bool readyToZero = false;
    static bool readyToShoot = false;



    static bool autonInit = false; //First loop initilization
    static bool hasAutonRun = false; //Is our auton still running?
    static bool aiming = false;
    static bool isCommandingHood = false;
    static bool hasStartedFeeding = false;
  //  static bool doneDriving = false;
  //  static bool readyToAim = false;
    static frc::Timer autonDriveTimer; //Used to track how long to drive for
    static frc::Timer autonShootTimer; //Used to track when we can shoot (basically waiting for spin up to complete)
    static frc::Timer autonFeedTimer;
    static frc::Timer aimingTimer;

    turret.limelight_led(true);
    if(hasAutonRun)
    {
            if(turret.getHoodValue() > SHOOTER::HOOD::SAFE_TO_TURN)
            {
                turret.traverseHood();
                turret.aimZero();
            }
            aiming = false;
            turret.limelight_led(false);
            turret.traverseHood();
            //turret.stopShooter();
            //activeIntake = false;
            isCommandingHood = false;
            //std::cout << "Done With Auton" std::endl;
    }

    //Start spooling up shooter wheel
    //turret.bangbangControl();
    if (!autonInit)
    {
        autonDriveTimer.Reset();
        autonDriveTimer.Start();
        autonShootTimer.Reset();
        autonShootTimer.Start();
        
        autonInit = true;
    }


    if (!autonDriveTimer.HasPeriodPassed(AUTON::AUTON_DRIVE_TIMER) && !hasAutonRun && !doneDriving)
    {
        intake.deploy(true);
        //activeIntake = true;
        //std::cout << "Driving" << std::endl;
        //drive.drive(-.2,-.2);
    }
    else
    {
        doneDriving = true;
        readyToAim = true;
        
    }

    if (doneDriving && readyToAim)
    {
        //std::cout << "Aiming Right" << std::endl;
       // turret.aimRightPID();
       // turret.traverseHood();
        //drive.drive(0,0);
                turret.aimRightPID();
                turret.traverseHood();
                aimingTimer.Start();
                std::cout << "Trying to aim right" << std::endl;

            if( aimingTimer.HasPeriodPassed(AUTON::AUTON_LIMELIGHT_TIMER))
            {
                readyToTrack = true;
                readyToAim = false;
            }
            
    }

    if( readyToTrack && doneDriving && !readyToAim)
    {
        std::cout << "Aiming with camera" << std::endl;
        if ( turret.getTurnyTurnyValue() > SHOOTER::TURRET::BACKWARDS - 2 
                    && turret.getTurnyTurnyValue() < SHOOTER::TURRET::BACKWARDS + 2 )
        {        
            turret.aimWithCameraLimelight();
            if(turret.cameraHasLock())
            {
                readyToShoot = true;
            }
        }

    }

    if (readyToShoot)
    {
        turret.aimWithCameraLimelight();
        if(autonShootTimer.HasPeriodPassed(AUTON::AUTON_SHOOT_TIMER))
        {
            hopper.feedShooter();
            autonFeedTimer.Start();
        }
        if(autonFeedTimer.HasPeriodPassed(AUTON::AUTON_FEED_SHOOTER_TIMER))
        {
            readyToZero = true;
            readyToShoot = false;
            hopper.stopFeed();
        }
    }

    if(readyToZero)
    {
        intake.deploy(false);
        turret.traverseHood();
        if(turret.getHoodValue() > SHOOTER::HOOD::SAFE_TO_TURN)
            {
                turret.zeroHood();
                turret.traverseHood();
            }
    }
    

    if(autonDriveTimer.HasPeriodPassed(AUTON::AUTON_MAX_TIMER))
    {
        readyToZero = true;
        readyToShoot = false;
        hasAutonRun = true;
    }



    /*if ( !autonDriveTimer.HasPeriodPassed(AUTON::AUTON_DRIVE_TIMER) && !hasAutonRun && !doneDriving)
    {
        //drive.drive(-.2,-.2); //Drive half speed backwards away from goal
        intake.deploy(true);
        activeIntake = true;

    }
    */
    else
    {   doneDriving = true;
        autonDriveTimer.Stop();
        //drive.drive(0,0);
        if (!aiming)
            {
                turret.aimRightPID();
                turret.traverseHood();
                if ( turret.getTurnyTurnyValue() > SHOOTER::TURRET::BACKWARDS - 2 
                  && turret.getTurnyTurnyValue() < SHOOTER::TURRET::BACKWARDS + 2 )
                {
                    aiming = true;
                }
                
            }
        readyToAim = true;

    }

    if ( !autonShootTimer.HasPeriodPassed(AUTON::AUTON_SHOOT_TIMER) && !hasAutonRun && doneDriving && readyToAim)
    {
        turret.aimWithCameraLimelight();
    }
    else
    {
        
        turret.aimWithCameraLimelight();
        if( turret.cameraHasLock() )
        {
            
            hopper.feedShooter();
            if(!hasStartedFeeding)
            {
                hasStartedFeeding = true;
            }
            if( hasStartedFeeding )
            {
                autonFeedTimer.Stop();
                autonFeedTimer.Start();
            }
        }

        if ( autonFeedTimer.HasPeriodPassed(AUTON::AUTON_FEED_SHOOTER_TIMER) )
        {

            hopper.stopFeed();
            hasAutonRun = true;
            intake.deploy(false);
            if(turret.getHoodValue() > SHOOTER::HOOD::SAFE_TO_TURN)
            {
                turret.zeroHood();
                turret.aimZero();
            }
        }
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
