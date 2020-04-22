#include "Drivetrain.hpp"
#include <iostream>

Drivetrain::Drivetrain()
{
}

void Drivetrain::reset()
{
    ldrive.sensors.SetIntegratedSensorPosition(0);
    rdrive.sensors.SetIntegratedSensorPosition(0);
}

bool Drivetrain::driveDistanceForward(double distance)
{
    static bool isReset = false;
    if(!isReset)
    {
        reset();
        isReset=true;
    }
    if((fabs(rdrive.getEncoderDistance())+fabs(ldrive.getEncoderDistance()))/2<fabs(distance))
    {
        if(fabs(rdrive.getEncoderDistance())<fabs(ldrive.getEncoderDistance()))
        {
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
        return false;
    }
    else
    {
        drive(0,0);
        return true;
    }
}

void Drivetrain::printDistance()
{
    std::cout << "Left: " << ldrive.getEncoderDistance() << std::endl;
    std::cout << "Right: " << rdrive.getEncoderDistance() << std::endl;
}

bool Drivetrain::driveDistanceBackward(double distance) // TODO: fix this
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
        return false;
    }
    drive(0,0);
    return true;
}


void Drivetrain::drive(double lval, double rval)
{
    rdrive.Set(-rval);
    ldrive.Set(lval);
}

void Drivetrain::shift()
{
    auto const drivetrain_speed = fabs(ldrive.sensors.GetIntegratedSensorVelocity() - rdrive.sensors.GetIntegratedSensorVelocity()) / 2;

    if(drivetrain_speed > TRANSMISSION::SHIFT_UP_POINT)
        shifter.Set(1);
    if(drivetrain_speed < TRANSMISSION::SHIFT_DOWN_POINT)
        shifter.Set(0);
}