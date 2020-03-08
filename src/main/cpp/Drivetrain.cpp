#include "Drivetrain.hpp"
#include <iostream>

Drivetrain::Drivetrain()
{
    //orchestra.LoadMusic(Paint_it_black.chrp);
    
    //orchestra.Play();

    //std::cout << 
}

void Drivetrain::reset()
{
    ldrive.sensors.SetIntegratedSensorPosition(0);
    rdrive.sensors.SetIntegratedSensorPosition(0);
   // ldrive.senssetEncoderDistance(0);
    //rdrive.setEncoderDistance(0);
}

bool Drivetrain::stillDriving()
{
    return isDriving;
}

void Drivetrain::driveDistanceForward(double distance)
{
    static bool isReset = false;
    if(!isReset)
    {
        reset();
        isReset=true;
    }
    if((fabs(rdrive.getEncoderDistance())+fabs(ldrive.getEncoderDistance()))/2<fabs(distance))
    {
        isDriving = true;
        if(fabs(rdrive.getEncoderDistance())<fabs(ldrive.getEncoderDistance()))
        {
            isDriving = true;
            if(fabs(rdrive.getEncoderDistance())>fabs(ldrive.getEncoderDistance()))
            {
                drive(-.35,-.25);
            }
            else if(fabs(rdrive.getEncoderDistance())<fabs(ldrive.getEncoderDistance()))
            {
                drive(-.25,-.35);
            }
            else
            {
                drive(-.25,-.25);
            }
        }
        else
        {
            drive(-.25,-.25);
        }
    }
    else
    {
        drive(0,0);
        isDriving = false;
    }
}

void Drivetrain::printDistance()
{
    std::cout << "Left: " << ldrive.getEncoderDistance() << std::endl;
    std::cout << "Right: " << rdrive.getEncoderDistance() << std::endl;
}

void Drivetrain::driveDistanceBackward(double distance)
{
    static bool isReset = false;
    if(!isReset)
    {
        reset();
        isReset=true;
    }
    if((fabs(rdrive.getEncoderDistance())+fabs(ldrive.getEncoderDistance()))/2<fabs(distance))//96
    {
        std::cout << "Going back" << std::endl;
        isDriving = true;
        if(fabs(rdrive.getEncoderDistance())>fabs(ldrive.getEncoderDistance()))
        {
            drive(.3,.4);
        }
        else if(fabs(rdrive.getEncoderDistance())<fabs(ldrive.getEncoderDistance()))
        {
            drive(.4,.3);
        }
        else
        {
            drive(.3,.3);
        }
    }
    else
    {
        drive(0,0);
        isDriving = false;
    }
}


void Drivetrain::drive(double lval, double rval)
{
    rdrive.Set(-rval);
    ldrive.Set(lval);


    
    auto const drivetrain_speed = fabs(ldrive.sensors.GetIntegratedSensorVelocity() - rdrive.sensors.GetIntegratedSensorVelocity()) / 2;
}

void Drivetrain::driveFalcons(double lval, double rval)
{
    rdrive->Set(ControlMode::PercentOutput,-rval);
    ldrive->Set(ControlMode::PercentOutput,lval);
}

void Drivetrain::shift()
{
    auto const drivetrain_speed = fabs(ldrive.sensors.GetIntegratedSensorVelocity() - rdrive.sensors.GetIntegratedSensorVelocity()) / 2;

    if(drivetrain_speed > TRANS::shift_up_point)
        shifter.Set(1);
    if(drivetrain_speed < TRANS::shift_down_point)
        shifter.Set(0);
}