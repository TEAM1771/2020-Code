#include "Intake.hpp"

Intake::Intake()
{
    intakeneo.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

void Intake::deploy(bool val)
{
    intakeair.Set(val);
}