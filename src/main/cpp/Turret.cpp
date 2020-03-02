
#include "Turret.hpp"
#include <vector>


Turret::Turret()
{

    //Limelight setup
    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
 
    //Shooter wheel setup
    shooter_1.RestoreFactoryDefaults();
    shooter_2.RestoreFactoryDefaults();

    shooter_2.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    shooter_1.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
   // shooter_1.SetOpenLoopRampRate(3);
   // shooter_2.SetOpenLoopRampRate(3);

   /* shooter_1.Follow(shooter_2, true);
    shooter_pidController.SetFeedbackDevice(shooter_encoder);
    shooter_pidController.SetP(SHOOTER::WHEEL::P);
    shooter_pidController.SetI(SHOOTER::WHEEL::I);
    shooter_pidController.SetD(SHOOTER::WHEEL::D);
    shooter_pidController.SetFF(SHOOTER::WHEEL::FF);
    shooter_pidController.SetReference(SHOOTER::WHEEL::SHOOTING_RPM, rev::ControlType::kVelocity);
    */
    //shooter_encoder.SetInverted(true);
    //TurretTurnyTurny setup
    turretTurnyTurny.RestoreFactoryDefaults();
    turretTurnyTurny.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    turretTurnyTurny_pidController.SetP(SHOOTER::TURRET::P);
    turretTurnyTurny_pidController.SetI(SHOOTER::TURRET::I);
    turretTurnyTurny_pidController.SetD(SHOOTER::TURRET::D);
    turretTurnyTurny_pidController.SetFeedbackDevice(turretTurnyTurny_encoder);
    //turretTurnyTurny_pidController.SetReference(SHOOTER::TURRET::ZERO, rev::ControlType::kPosition);
    turretTurnyTurny_pidController.SetOutputRange(-.7, .7);
   // turretTurnyTurny.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
   // turretTurnyTurny.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
   // turretTurnyTurny.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::TURRET::MAX_LEFT);
   // turretTurnyTurny.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::TURRET::MAX_RIGHT);
    

    //Hood setup
    hood.RestoreFactoryDefaults();
    hood.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    
    hood_pidController.SetP(SHOOTER::HOOD::P);
    hood_pidController.SetI(SHOOTER::HOOD::I);
    hood_pidController.SetD(SHOOTER::HOOD::D);
    hood_pidController.SetFeedbackDevice(hood_encoder);
    hood_pidController.SetReference(SHOOTER::HOOD::BOTTOM, rev::ControlType::kPosition);
    hood_pidController.SetOutputRange(-.8,.8);
   // hood.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
   // hood.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
   // hood.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::HOOD::TOP);
   // hood.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::HOOD::BOTTOM);
    double hoodSetpoint = 0;
    getCameraData();
     frc::SmartDashboard::PutNumber("Hood Setpoint", hoodSetpoint);
     frc::SmartDashboard::PutNumber("Y Offset", cameraYValue);
}


/*
void Turret::aimBackwards()
{
    turretTurnyTurny_pidController.SetReference(SHOOTER::TURRET::BACKWARDS, rev::ControlType::kPosition);
}

void Turret::aimForward()
{
    turretTurnyTurny_pidController.SetReference(SHOOTER::TURRET::FORWARD, rev::ControlType::kPosition);
} 
*/

void Turret::stopShooter()
{
    shooter_1.Set(0);
    shooter_2.Set(0);
}

bool Turret::valueInRange(double value, double min, double max)
{
    if ( (value >= min) && (value <= max) )
    {
         return true;
    }
    else
    {
        return false;
    }
    
}

void Turret::bangbangControl()
{
   /* if ( valueInRange(abs( shooter_encoder.GetVelocity() ) ,SHOOTER::WHEEL::SHOOTING_RPM - 900, SHOOTER::WHEEL::SHOOTING_RPM - 500) )
    {
        shooter_1.SetOpenLoopRampRate(0.2);
        shooter_2.SetOpenLoopRampRate(0.2);
        shooter_1.Set(-.7);
        shooter_2.Set(7);
        std::cout << "area1" << std::endl;
    }
    else */if( valueInRange(abs( shooter_encoder.GetVelocity() ), SHOOTER::WHEEL::SHOOTING_RPM - 2000, SHOOTER::WHEEL::SHOOTING_RPM) )
    {
        shooter_1.SetOpenLoopRampRate(0);
        shooter_2.SetOpenLoopRampRate(0);
        shooter_1.Set(-1);
        shooter_2.Set(1);  
        //std::cout << "area2" << std::endl;
    }
    else if ( (abs(shooter_encoder.GetVelocity() ) < SHOOTER::WHEEL::SHOOTING_RPM ))
    {
        shooter_1.SetOpenLoopRampRate(5.1771);
        shooter_2.SetOpenLoopRampRate(5.1771);
        shooter_1.Set(-1);
        shooter_2.Set(1);  
        //std::cout << "area3" << std::endl;
    }
    else
    {
        shooter_1.Set(0);
        shooter_2.Set(0);
        //shooter_1.SetOpenLoopRampRate(0);
        //shooter_2.SetOpenLoopRampRate(0);
        // std::cout << "area4" << std::endl;
    }
    
    
}

void Turret::aimWithCameraLimelight()
{
    //frc::SmartDashboard::GetNumber("Hood Position", hoodSetpoint));
    getCameraData();
    if (cameraHasTarget)
    {
        double xOffset = cameraXValue + SHOOTER::TURRET::CAMERA_OFFSET;
        double output = xOffset/35;
        double const currentTicks = turretTurnyTurny_encoder.GetPosition();
        if (currentTicks < SHOOTER::TURRET::MAX_RIGHT 
         && currentTicks > SHOOTER::TURRET::MAX_LEFT)
        {
            turretTurnyTurny.Set(output);
        }
        else
        {
            turretTurnyTurny.Set(0);
        }
        
        std::cout << "yval: " << cameraYValue << '\n';
        double const yval = getHoodAngle(cameraYValue);
        std::cout << "hood: " << yval << std::endl;
        setHoodAngle(yval);
    }
    else
    {
          turretTurnyTurny.Set(0);
    }

}

double Turret::getCameraY()
{
    getCameraData();
    if(cameraHasTarget)
        return cameraYValue;
    else return -100;
}

void Turret::aimWithCamera()
{  
    //Aim to the center of the target
    getCameraData();
    //Figure out some offset based on camera data?
    if (cameraHasTarget)
    {
        //Insert math to scale here
        const int cameraXMidPoint = 320 / 2;
        const int cameraXOffset = cameraXValue - cameraXMidPoint;
        //Need to scale output to be -1:1 based on cameraOffset 
        double const output = scaleOutput(0,320,-1,1, cameraXOffset);
        turretTurnyTurny.Set(output);

        double const yval = getHoodAngle(cameraYValue);
        setHoodAngle(yval);
    }
    else
    {
        turretTurnyTurny.Set(0);
    }

}

void Turret::traverseHood()
{
    hood_pidController.SetReference(SHOOTER::HOOD::TRAVERSE, rev::ControlType::kPosition);
}

double Turret::scaleOutput(double inputMin, double inputMax, double outputMin, double outputMax, double input)
{
   double output = ( (input - inputMin) / (inputMax - inputMin) ) * ( ( outputMax - outputMin) ) + inputMin;
   return output; 
}

void Turret::stopAiming()
{
    turretTurnyTurny.Set(0);
}

void Turret::getCameraData()
{
    //Do Something to get Network table data
    
    cameraXValue = table->GetNumber("tx",0.0);
    cameraYValue = table->GetNumber("ty",0.0);
    cameraHasTarget = table->GetNumber("tv",0.0);
    //cameraArea = table->GetNumber("ta", 0.0);
    
}


void Turret::rpmWithStick(float value)
{
    shooter_1.Set(value);
    shooter_2.Set(-value);
}

/**************************************************/
/*         Direct Position control functions      */
/**************************************************/


void Turret::aimLeft()
{
    if (turretTurnyTurny_encoder.GetPosition() > SHOOTER::TURRET::MAX_LEFT)
    {
        turretTurnyTurny.Set(-SHOOTER::TURRET::TRAVERSE_SPEED);
    }
    else
    {
        turretTurnyTurny.Set(0);
    }
}

void Turret::aimRight()
{
    if (turretTurnyTurny_encoder.GetPosition() < SHOOTER::TURRET::MAX_RIGHT)
    {
        turretTurnyTurny.Set(SHOOTER::TURRET::TRAVERSE_SPEED);
    }
    else
    {
        turretTurnyTurny.Set(0);
    }
}

void Turret::aimLeftPID()
{
    //turretTurnyTurny_pidController.Set
    turretTurnyTurny_pidController.SetReference(SHOOTER::TURRET::FORWARD, rev::ControlType::kPosition);
    //std::cout << turretTurnyTurny_pidController
}

void Turret::aimRightPID()
{
     turretTurnyTurny_pidController.SetReference(SHOOTER::TURRET::BACKWARDS, rev::ControlType::kPosition);
}

void Turret::aimZero()
{
     turretTurnyTurny_pidController.SetReference(SHOOTER::TURRET::ZERO, rev::ControlType::kPosition);
}

void Turret::maintainRPM()
{
    shooter_pidController.SetReference(SHOOTER::WHEEL::SHOOTING_RPM, rev::ControlType::kVelocity);
}

void Turret::zeroHood()
{
        hood_pidController.SetReference(SHOOTER::HOOD::BOTTOM, rev::ControlType::kPosition);
}

void Turret::midHood()
{
        hood_pidController.SetReference(SHOOTER::HOOD::MIDPOINT, rev::ControlType::kPosition);
}

void Turret::batterHood()
{
    hood_pidController.SetReference(SHOOTER::HOOD::BATTER, rev::ControlType::kPosition);

}


void Turret::limelight_led(bool val)
{
    table->PutNumber("ledMode",val? 3 : 1);
}

/************************************************************/
/*          getters / display functions                     */
/************************************************************/
void Turret::giveStatus()
{
   // std::cout << "Turny: " << turretTurnyTurny_encoder.GetPosition() << std::endl;
  //  std::cout << "shoot1 " << shooter_1.GetAppliedOutput() << "\n";
  //  std::cout << "shoot2 " << shooter_2.GetAppliedOutput() << "\n";
  //  std::cout << "Hood: "  << hood_encoder.GetPosition() << std::endl;
   // std::cout << "Shooter actual: " << abs(shooter_encoder.GetVelocity()) << std::endl;
   getCameraData();
   //std::cout << "X: " << cameraXValue << "\n";
  // std::cout << "Y: " << cameraYValue << std::endl;
  // if (cameraHasTarget)
  // {
  // std::cout << "Target! :" << std::endl;
  // }

}

double Turret::getHoodValue()
{
    return hood_encoder.GetPosition();
}

double Turret::getTurnyTurnyValue()
{
    return turretTurnyTurny_encoder.GetPosition();
}

void Turret::setHoodAngle(double position)
{
    hood_pidController.SetReference(position, rev::ControlType::kPosition);
}

//To be called from robot.cpp, will handle all autonomous self containing functions 
void Turret::controlTurret()
{
    turnyturnyEncoderTicks = turretTurnyTurny_encoder.GetPosition();
}

//Height is the Y value of the camera tracking the target
double Turret::getHoodAngle(double height)
{
    
    //return -30;
    //YValues table is the camera reading
    //Hood table is the hood position
    std::vector<double> const YValues   { 20.0104, 10.4538, 1.97857, -3.02635, -5.8812, -9.15754 }; 
    std::vector<double> const hoodTable { -13.1929, -17.0433, -21.375, -22.0117, -21.6297, -21.375 };
    
    //Check if height is higher than anything in the table (indicating we are closer, thus should set hood to the minimum value)
    /*if ( height < YValues[0] )
    {
        return SHOOTER::HOOD::TRAVERSE;
    }
    //Check if height is lower than anything in the table (indicating we are farther than anything, thus should set hood to the max)
    else if (height > *std::prev(YValues.end()) )
    {
        return SHOOTER::HOOD::SAFE_TO_TURN;
    }*/

    int position = 1;

    for (unsigned int i = 0; i <= YValues.size(); i++) {
        if ((height <= YValues[i])
                && (height >= YValues[i + 1])) {
            //assign a "position" to be used later on
            //200,180,166,154,143,132,123,115,108,102
            position = i;

        }
    }
    
    //here is where position is used, for the linear interp.
    double const valueToReturn = (((hoodTable[position] - hoodTable[position + 1])
            / (YValues[position] - YValues[position + 1]))
            * (height - YValues[position + 1]))
            + hoodTable[position + 1];

    std::cout << "hood precheck: " << valueToReturn << '\n';
    if(valueToReturn < SHOOTER::HOOD::SAFE_TO_TURN)
        return SHOOTER::HOOD::SAFE_TO_TURN;
    else if (valueToReturn > SHOOTER::HOOD::TRAVERSE)
        return SHOOTER::HOOD::TRAVERSE;
   // double valueToReturn = 0;
    return valueToReturn;
}

void Turret::debugSetHoodAngle(double position)
{
    //hood_pidController.SetReference(position, rev::ControlType::kPosition);
}