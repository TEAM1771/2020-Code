#pragma once

#include "Constants.hpp"
#include "ctre\phoenix\music\Orchestra.h"
#include "transmission.hpp"
#include <frc\Solenoid.h>

class Drivetrain
{
    Transmission rdrive { TRANSMISSION::RIGHT_MOTOR };
    Transmission ldrive { TRANSMISSION::LEFT_MOTOR };

    frc::Solenoid shifter { TRANSMISSION::SHIFTER };

    struct DriveDistance
    {
        double rDist;
        double lDist;
        double netDist;
    };

public:
    Drivetrain();
    void drive(double lval, double rval);

    bool driveDistanceForward(double distance, bool reset = false);
    bool driveDistanceBackward(double distance, bool reset = false);

    void          printDistance() const;
    DriveDistance getDistance() const;

    void reset();

    void shift();
};