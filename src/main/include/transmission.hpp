#pragma once

#include <rev\CANSparkMax.h>
#include <ctre\Phoenix.h>

#include "Constants.hpp"

class Transmission
{
    ctre::phoenix::motorcontrol::can::TalonFX falcon;

public:
    Transmission(int falcon_adr);
    double getEncoderDistance();
    void setEncoderDistance(double distance);

    ctre::phoenix::motorcontrol::can::TalonFX *operator->(); // used to access the falcons directly

    void Set(double val);

    ctre::phoenix::motorcontrol::TalonFXSensorCollection& sensors;
};