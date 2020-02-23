#include "Hopper.hpp"
#include <iostream>

Hopper::Hopper()
{
    indexerNeo.Set(HOPP::hopperIndexerForward);
    indexerNeo.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    transportNeo.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

bool Hopper::isLaserBroken() const
{
    return beamBreak.Get();
}

void Hopper::transportBall()
{
    
}
void Hopper::feedShooter()
{
    transportNeo.Set(HOPP::hopperTransportForward);

}
void Hopper::stopFeed()
{
    transportNeo.Set(0);
}