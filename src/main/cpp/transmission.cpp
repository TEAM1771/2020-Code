#include "transmission.hpp"

Transmission::Transmission(int falcon_adr, int neo_adr):
    falcon { falcon_adr },
    neo ( neo_adr, rev::CANSparkMaxLowLevel::MotorType::kBrushless )
{
    neo.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    sensors = falcon.GetSensorCollection();
}

ctre::phoenix::motorcontrol::can::TalonFX *Transmission::operator->()
{
    return &falcon;
}

void Transmission::Set(double val)
{
    neo.Set(val);
    falcon.Set(ControlMode::PercentOutput, val);
}
