#pragma once

#include "transmission.hpp"
#include "Constants.hpp"

#include "ctre\phoenix\music\Orchestra.h"
#include <frc\Solenoid.h>

class Drivetrain
{
    Transmission rdrive { TRANSMISSION::RIGHT_MOTOR };
    Transmission ldrive { TRANSMISSION::LEFT_MOTOR };

    frc::Solenoid shifter { TRANSMISSION::SHIFTER };

public:
    Drivetrain();
    void drive(double lval, double rval);

    bool driveDistanceForward(double distance);
    bool driveDistanceBackward(double distance);

    void printDistance();

    void reset();

    void shift();
};