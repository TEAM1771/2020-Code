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

   // shooter_2.Follow(shooter_1, true);
   // shooter_pidController.SetFeedbackDevice(shooter_encoder);
   // shooter_pidController.SetP(SHOOTER::WHEEL::P);
   // shooter_pidController.SetI(SHOOTER::WHEEL::I);
   // shooter_pidController.SetD(SHOOTER::WHEEL::D);
   // shooter_pidController.SetReference(SHOOTER::WHEEL::SHOOTING_RPM, rev::ControlType::kVelocity);

    //TurretTurnyTurny setup
    turretTurnyTurny.RestoreFactoryDefaults();
    turretTurnyTurny.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    turretTurnyTurny_pidController.SetP(SHOOTER::TURRET::P);
    turretTurnyTurny_pidController.SetI(SHOOTER::TURRET::I);
    turretTurnyTurny_pidController.SetD(SHOOTER::TURRET::D);
    turretTurnyTurny_pidController.SetFeedbackDevice(turretTurnyTurny_encoder);
    turretTurnyTurny_pidController.SetReference(SHOOTER::TURRET::FORWARD, rev::ControlType::kPosition);
   // turretTurnyTurny.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
   // turretTurnyTurny.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
   // turretTurnyTurny.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::TURRET::MAX_LEFT);
   // turretTurnyTurny.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::TURRET::MAX_RIGHT);
    

    //Hood setup
   // hood.RestoreFactoryDefaults();
   // hood.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
   // hood_pidController.SetP(SHOOTER::HOOD::P);
   // hood_pidController.SetI(SHOOTER::HOOD::I);
   // hood_pidController.SetD(SHOOTER::HOOD::D);
   // hood_pidController.SetFeedbackDevice(hood_encoder);
   // hood_pidController.SetReference(SHOOTER::HOOD::BOTTOM, rev::ControlType::kPosition);
   // hood.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
   // hood.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
   // hood.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::HOOD::TOP);
   // hood.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::HOOD::BOTTOM);


}

//To be called from robot.cpp, will handle all autonomous self containing functions 
void Turret::controlTurret()
{
    turnyturnyEncoderTicks = turretTurnyTurny_encoder.GetPosition();
}

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

void Turret::giveStatus()
{
    std::cout << "Turny: " << turretTurnyTurny_encoder.GetPosition() << "\n";
 //   std::cout << "Hood: "  << hood_encoder.GetPosition() << "\n";
    std::cout << "Shooter actual: " << shooter_encoder.GetVelocity() << std::endl;

}

void Turret::setHoodAngle(double position)
{
    hood_pidController.SetReference(position, rev::ControlType::kPosition);
}

void Turret::bangbangControl()
{
    if (abs(shooter_encoder.GetVelocity()) <  (SHOOTER::WHEEL::SHOOTING_RPM - 1000) )
        {
            shooter_1.Set(-.7);
            shooter_2.Set(7);
        }
    else if (abs(shooter_encoder.GetVelocity()) < SHOOTER::WHEEL::SHOOTING_RPM  )
        {
            shooter_1.Set(-1);
            shooter_2.Set(1);
        }
    else
        {
            shooter_1.Set(0);
            shooter_2.Set(0);
        }
    
    
}

void Turret::aimWithCamera()
{  
    //Aim to the center of the target
    getCameraData();
    //Figure out some offset based on camera data?
    if (cameraHasTarget)
    {
    //Insert math to scale here
        double output;
        const int cameraXMidPoint = 320 / 2;
        const int cameraXOffset = cameraXValue - cameraXMidPoint;
        //Need to scale output to be -1:1 based on cameraOffset 
        output = scaleOutput(0,320,-1,1, cameraXOffset);
        turretTurnyTurny.Set(output);
        double heightPosition;
       // const int cameraYMidPoint = 240/2;
        heightPosition = getHoodAngle(cameraYValue);
        setHoodAngle(heightPosition);
    }
    else
    {
        turretTurnyTurny.Set(0);
    }

}

//Height is the Y value of the camera tracking the target
double Turret::getHoodAngle(double height)
{
    /*
    //YValues table is the camera reading
    //Hood table is the hood position
    std::vector<double> const YValues { 200, 180, 166, 154, 143, 132, 123, 115, 108, 102 }; 
    std::vector<double> const hoodTable {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    //Check if height is higher than anything in the table (indicating we are closer, thus should set hood to the minimum value)
    if ( height > YValues[0] )
    {
        return 0.0;
    }
    //Check if height is lower than anything in the table (indicating we are farther than anything, thus should set hood to the max)
    else if (height < std::prev(YValues.end()) )
    {
        return 100;
    }

    double valueToReturn;
    int position;

    for (int i = 0; i <= YValues.size(); i++) {
        if ((height <= YValues[i])
                && (height >= YValues[i + 1])) {
            //assign a "position" to be used later on
            //200,180,166,154,143,132,123,115,108,102
            position = i;

        }
    }
    
    //here is where position is used, for the linear interp.
    valueToReturn = (((hoodTable[position] - hoodTable[position + 1])
            / (YValues[position] - YValues[position + 1]))
            * (height - YValues[position + 1]))
            + hoodTable[position + 1];

*/
    double valueToReturn = 0;
    return valueToReturn;

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
    cameraHasTarget = table->GetBoolean("tv",0.0);
    cameraArea = table->GetNumber("ta", 0.0);
}

void Turret::aimLeftPID()
{
    //turretTurnyTurny_pidController.Set
    turretTurnyTurny_pidController.SetReference(-600, rev::ControlType::kPosition);
    //std::cout << turretTurnyTurny_pidController
}

void Turret::aimRightPID()
{
     turretTurnyTurny_pidController.SetReference(600, rev::ControlType::kPosition);
}

void Turret::maintainRPM()
{
    shooter_1.Set(1);
    shooter_2.Set(-1);
}

void Turret::rpmWithStick(float value)
{
    shooter_1.Set(value);
    shooter_2.Set(-value);
}
