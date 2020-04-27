#pragma once

#include "Constants.hpp"
#include "ctre\phoenix\music\Orchestra.h"
#include "transmission.hpp"
#include <frc\Solenoid.h>

class Drivetrain
{
    Transmission  rdrive { TRANS::rFalcon, TRANS::rNeo };
    Transmission  ldrive { TRANS::lFalcon, TRANS::lNeo };
    Orchestra     orchestra;
    bool          isDriving;
    frc::Solenoid shifter { TRANS::shifter };

public:
    Drivetrain();
    void drive(double lval, double rval);
    void driveFalcons(double lval, double rval);
    void driveDistanceForward(double distance);
    void driveDistanceBackward(double distance);
    void printDistance();

    bool stillDriving();

    void reset();

    void shift();
};