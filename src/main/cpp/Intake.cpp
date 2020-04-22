#include "Intake.hpp"

Intake::Intake()
{
    wheels.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    intakeDeployed = false;
}

void Intake::deploy(bool val)
{
    intakeair.Set(val);
    intakeDeployed = val;
} 

bool Intake::isIntakeDown() const
{
    return intakeDeployed;
}
