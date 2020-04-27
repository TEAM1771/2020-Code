#include "Intake.hpp"

Intake::Intake()
{
    intakeneo.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    intakeDeployed = false;
}

void Intake::deploy(bool val)
{
    intakeair.Set(val);
    intakeDeployed = val;
}

bool Intake::isIntakeDown()
{
    return intakeDeployed;
}
