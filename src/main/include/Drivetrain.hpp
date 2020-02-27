#pragma once

#include "transmission.hpp"
#include "Constants.hpp"

#include "ctre\phoenix\music\Orchestra.h"
#include <frc\Solenoid.h>

class Drivetrain
{
    Transmission rdrive { TRANS::rFalcon, TRANS::rNeo };
    Transmission ldrive { TRANS::lFalcon, TRANS::lNeo };
    Orchestra orchestra;
    
    frc::Solenoid shifter { 0 };
public:
    Drivetrain();
    void drive(double lval, double rval);
    void driveFalcons(double lval, double rval);

    void shift();
};