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
    ldrive.setEncoderDistance(0);
    rdrive.setEncoderDistance(0);
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
        if(fabs(rdrive.getEncoderDistance())>fabs(ldrive.getEncoderDistance()))
        {
            drive(-.2,-.3);
        }
        else if(fabs(rdrive.getEncoderDistance())<fabs(ldrive.getEncoderDistance()))
        {
            drive(-.3,-.2);
        }
        else
        {
            drive(-.2,-.2);
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
    //std::cout << "Left: " << ldrive.getEncoderDistance() << std::endl;
    //std::cout << "Right: " << rdrive.getEncoderDistance() << std::endl;
}

void Drivetrain::driveDistanceBackward(double distance)
    {
        static bool isReset = false;
        if(!isReset)
        {
            reset();
            isReset=true;
        }
        if((fabs(rdrive.getEncoderDistance())+fabs(ldrive.getEncoderDistance()))/2>fabs(distance))//96
        
                {
                                isDriving = true;

                        if(fabs(rdrive.getEncoderDistance())>fabs(ldrive.getEncoderDistance()))
                        {
                                drive(-3.,-.2);
                                //SetLeftJags(1);
                               // SetRightJags(-.5);
                        }
                        else if(fabs(rdrive.getEncoderDistance())<fabs(ldrive.getEncoderDistance()))
                        {
                                drive(-.2,-.3);
                                //SetLeftJags(.5);
                                //SetRightJags(-1);
                        }
                        else
                        {
                                drive(-.2,-.2);
                               // SetLeftJags(1);
                               // SetRightJags(-1);
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