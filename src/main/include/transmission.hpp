#pragma once

#include <rev\CANSparkMax.h>
#include <ctre\Phoenix.h>

class Transmission
{
    ctre::phoenix::motorcontrol::can::TalonFX falcon;
    rev::CANSparkMax neo;

public:
    Transmission(int falcon_adr, int neo_adr);

    ctre::phoenix::motorcontrol::can::TalonFX *operator->(); // used to access the falcons directly

    void Set(double val);

    ctre::phoenix::motorcontrol::TalonFXSensorCollection& sensors;
};