#include "Turret.hpp"


Turret::Turret()
{

    //Limelight setup
    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
 
    //Shooter wheel setup
    shooter_1.RestoreFactoryDefaults();
    shooter_2.RestoreFactoryDefaults();

    shooter_2.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    shooter_1.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

    shooter_2.Follow(shooter_1, true);
    shooter_pidController.SetFeedbackDevice(shooter_encoder);
    shooter_pidController.SetP(SHOOTER::WHEEL::P);
    shooter_pidController.SetI(SHOOTER::WHEEL::I);
    shooter_pidController.SetD(SHOOTER::WHEEL::D);
    shooter_pidController.SetReference(SHOOTER::WHEEL::SHOOTING_RPM, rev::ControlType::kVelocity);

    //TurretTurnyTurny setup
    turretTurnyTurny.RestoreFactoryDefaults();
    turretTurnyTurny.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
   /* turretTurnyTurny_pidController.SetP(SHOOTER::TURRET::P);
    turretTurnyTurny_pidController.SetI(SHOOTER::TURRET::I);
    turretTurnyTurny_pidController.SetD(SHOOTER::TURRET::D);
    turretTurnyTurny_pidController.SetFeedbackDevice(turretTurnyTurny_encoder);
    turretTurnyTurny_pidController.SetReference(SHOOTER::TURRET::FORWARD, rev::ControlType::kPosition);
    turretTurnyTurny.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
    turretTurnyTurny.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
    turretTurnyTurny.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::TURRET::MAX_LEFT);
    turretTurnyTurny.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::TURRET::MAX_RIGHT);
    */

    //Hood setup
    hood.RestoreFactoryDefaults();
    hood.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    hood_pidController.SetP(SHOOTER::HOOD::P);
    hood_pidController.SetI(SHOOTER::HOOD::I);
    hood_pidController.SetD(SHOOTER::HOOD::D);
    hood_pidController.SetFeedbackDevice(hood_encoder);
    hood_pidController.SetReference(SHOOTER::HOOD::BOTTOM, rev::ControlType::kPosition);
    hood.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
    hood.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
    hood.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::HOOD::TOP);
    hood.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, SHOOTER::HOOD::BOTTOM);


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
    std::cout << turretTurnyTurny_encoder.GetPosition() << std::endl;
}

void Turret::setHoodAngle(int position)
{
    hood_pidController.SetReference(position, rev::ControlType::kPosition);
}

void Turret::bangbangControl()
{
    if (shooter_encoder.GetVelocity() < SHOOTER::WHEEL::SHOOTING_RPM)
        {
            shooter_1.Set(1);
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
        double output = 1;
        turretTurnyTurny.Set(output);
        turnyturnyEncoderTicks = turretTurnyTurny_encoder.GetPosition();
        int heightPosition = 1; //Figure this out
        setHoodAngle(heightPosition);
    }
    else
    {
        turretTurnyTurny.Set(0);
    }

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