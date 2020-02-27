#include "Drivetrain.hpp"
#include <iostream>

Drivetrain::Drivetrain()
{
    //orchestra.LoadMusic(Paint_it_black.chrp);
    
    //orchestra.Play();

    //std::cout << 
}

void Drivetrain::drive(double lval, double rval)
{
    rdrive.Set(-rval);
    ldrive.Set(lval);

    
    auto const drivetrain_speed = fabs(ldrive.sensors.GetIntegratedSensorVelocity() - rdrive.sensors.GetIntegratedSensorVelocity()) / 2;

    std::cout << drivetrain_speed << '\n';
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