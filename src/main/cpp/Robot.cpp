#include "Robot.hpp"
#include <frc/Timer.h>

Robot::Robot()
{
    activeIntake = false;
}

void Robot::AutonomousInit()
{
    drive.reset();
}

void Robot::FiveBallAuton()
{
    static bool doneDrivingForward = false;
    static bool doneDrivingBackward = false;
    static bool doneTurning = false;
    static bool doneAiming = false;
    static bool doneShooting = false;

    static frc::Timer turnTimer;
    static frc::Timer shootTimer;
    static frc::Timer aimTimer;
    static frc::Timer backTimer;
    //drive.printDistance();

    //HopperManager();

    turret.bangbangControl();
    turret.limelight_led(true);
    intake.deploy(true);
    intake.intakeneo.Set(-1);

    if(!doneDrivingForward)
    {
        turret.traverseHood();
        HopperManager();
        std::cout << "Trying to drive forward" << std::endl;
        drive.driveDistanceForward(AUTON::DISTANCE_FORWARD);
        if(!drive.stillDriving())
        {
            std::cout << "Done driving forward" << std::endl;
            drive.drive(0,0);
            doneDrivingForward = true;
            turnTimer.Reset();
            turnTimer.Start();
        }
    }
    else if(!doneTurning)
    {
        HopperManager();
        drive.drive(.3,0);
        turret.traverseHood();
        turret.aimRightPID();
        if(turnTimer.HasPeriodPassed(AUTON::TURN_TIME))
        {
            doneTurning = true;
            turnTimer.Stop();
            drive.drive(0,0);
            backTimer.Reset();
            backTimer.Start();
            //frc::Wait(0.2); //Wait to let momentum from the robot stop spinning it so we don't mess with encoder reset. Using Wait() is pretty sketchy, so we try not to use it. This is a good time to use it.
        }
    }
    
    else if(!doneDrivingBackward)
    {
        HopperManager();
        turret.traverseHood();
        turret.aimRightPID();
        std::cout << "Trying to drive backwards" << std::endl;
        drive.drive(.5,.5);
        if(backTimer.HasPeriodPassed(AUTON::TIME_BACKWARD))
        {
            std::cout << "Done driving backwards" << std::endl;
            drive.drive(0,0);

            backTimer.Stop();   
            doneDrivingBackward = true;
            aimTimer.Reset();
            aimTimer.Start();
        }
    }
    
    
    else if(!doneAiming)
    {
        HopperManager();
        std::cout << "Aiming with camera" << std::endl;
        if ( turret.getTurnyTurnyValue() > SHOOTER::TURRET::BACKWARDS - 2 
                    && turret.getTurnyTurnyValue() < SHOOTER::TURRET::BACKWARDS + 2 )
        {        
            //turret.aimWithCameraLimelight();
            if(turret.cameraHasLock() && aimTimer.HasPeriodPassed(AUTON::AUTON_LIMELIGHT_TIMER))
            {
                doneAiming = true;
                shootTimer.Reset();
                shootTimer.Start();
            }
        }
        else
        {
            turret.traverseHood();
            turret.aimRightPID();
        }
    }
    
    else if(!doneShooting) //Auton code can end here, hopper will be feeding shooter until auton ends
    {
        turret.aimWithCameraLimelight();
        if(shootTimer.HasPeriodPassed(AUTON::AUTON_SHOOT_TIMER))
        {
            hopper.feedShooter();
        }
    }
    

    
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
            //turret.limelight_led(false);
            turret.traverseHood();
            //turret.stopShooter();
            //activeIntake = false;
            isCommandingHood = false;
            //std::cout << "Done With Auton" std::endl;
    }

    //Start spooling up shooter wheel
    turret.bangbangControl();
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
        drive.drive(-.2,-.2);
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
        drive.drive(0,0);
        
        if(turret.getHoodValue() > SHOOTER::HOOD::SAFE_TO_TURN)
        {
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
    else
    {
        turret.traverseHood();
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
        else
        {
            turret.traverseHood();
            turret.aimRightPID();
        }
        

    }

    if (readyToShoot)
    {
        turret.aimWithCameraLimelight();
        if(autonShootTimer.HasPeriodPassed(AUTON::AUTON_SHOOT_TIMER_SIMPLE))
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

}

void Robot::AutonomousPeriodic() 
{
    SimpleAuton();
   // FiveBallAuton();
}

void Robot::TeleopInit()
{

}

void Robot::TeleopPeriodic()
{
    
    drive.drive(lStick.GetY(), rStick.GetY());
    drive.shift();

   
    HopperManager();
    //IntakeManager();
    ClimberManager();
    TurretManager();
}

void Robot::HopperManager()
{
    static bool isShooting = false;

    if(oStick.GetRawButton(BUTTONS::HOPPER::SHOOT))
    {
        hopper.feedShooter();    
    }
    else if(oStick.GetRawButtonReleased(BUTTONS::HOPPER::SHOOT))
    {
        hopper.stopFeed();
    }
    else
    {
      //  isShooting = false;
      //  std::cout << "RESETING" << std::endl;
        hopper.controlFeedPID();
    }
    
}

void Robot::TestPeriodic()
{
    //hopper.manualIndexerControl(lStick.GetY());
//hopper.manualTransportControl(rStick.GetY());
    //TurretManager();
    /*IntakeManager();

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
    */
   
  // ClimberManager();
  TurretManager();
  HopperManager();
 // turret.giveStatus();
   // HopperManager();
  // climber.joystickControl(oStick.GetY());
  // climber.printStatus();

}

void Robot::TurretManager()
{
        turret.limelight_led(true);
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
            //turret.bangbangControl();
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
            //turret.bangbangControl();
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
        else if (oStick.GetRawButton(BUTTONS::TURRET::SHOOT_FORWARD))
        {
            turret.setHoodAngle(-20);
        }
        /*else if (oStick.GetRawButton(BUTTONS::TURRET::AIM_LEFT_MANUAL))
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
          //  turret.limelight_led(false);
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
    static bool hasBeenPressed = false;
    if(oStick.GetThrottle() < 0 && oStick.GetRawButton(11))
    {
        climber.ClimbUp();
        hasBeenPressed = true;
    }
    else if(hasBeenPressed && oStick.GetThrottle() < 0)
    {
        climber.ClimbDown();
        hasBeenPressed = false;
        
    }
    climber.printStatus();
    
   /* if(lStick.GetRawButton(BUTTONS::CLIMBER::RAISE))
        climber.climb(true);
    else climber.climb(false);*/
}

void Robot::DisabledInit()
{

}

void Robot::DisabledPeriodic()
{
    //turret.giveStatus();
    //hopper.giveStatus();
    //drive.printDistance();
   // climber.printStatus();
}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
