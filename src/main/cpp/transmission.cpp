#include "transmission.hpp"

Transmission::Transmission(int falcon_adr, int neo_adr):
    falcon { falcon_adr },
  //  neo ( neo_adr, rev::CANSparkMaxLowLevel::MotorType::kBrushless ),
    sensors { falcon.GetSensorCollection() }
{
 //   neo.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    falcon.SetNeutralMode(NeutralMode::Coast);
    //sensors = falcon.GetSensorCollection();
}

ctre::phoenix::motorcontrol::can::TalonFX *Transmission::operator->()
{
    return &falcon;
}

void Transmission::Set(double val)
{
   // neo.Set(val);
    falcon.Set(ControlMode::PercentOutput, val);
}


double Transmission::getEncoderDistance()
{
    return sensors.GetIntegratedSensorPosition() / 2048;
   // return encoder.GetPosition();
}

void Transmission::setEncoderDistance(double distance)
{
    sensors.SetIntegratedSensorPosition(distance);
}
