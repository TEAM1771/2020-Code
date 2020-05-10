#include "ShooterWheel.hpp"

ShooterWheel::ShooterWheel()
{
    shooter_1.RestoreFactoryDefaults();
    shooter_2.RestoreFactoryDefaults();

    shooter_1.SetIdleMode(SHOOTER_WHEEL::IDLE_MODE);
    shooter_2.SetIdleMode(SHOOTER_WHEEL::IDLE_MODE);

    shooter_1.SetP(SHOOTER_WHEEL::P);
    shooter_1.SetI(SHOOTER_WHEEL::I);
    shooter_1.SetD(SHOOTER_WHEEL::D);
    shooter_1.SetDFilter(SHOOTER_WHEEL::F);
    shooter_1.SetFF(-SHOOTER_WHEEL::FF);
    shooter_1.SetTarget(-SHOOTER_WHEEL::SHOOTING_RPM, rev::ControlType::kVelocity);

    shooter_2.SetP(SHOOTER_WHEEL::P);
    shooter_2.SetI(SHOOTER_WHEEL::I);
    shooter_2.SetD(SHOOTER_WHEEL::D);
    shooter_2.SetDFilter(SHOOTER_WHEEL::F);
    shooter_2.SetFF(SHOOTER_WHEEL::FF);
    shooter_2.SetTarget(SHOOTER_WHEEL::SHOOTING_RPM, rev::ControlType::kVelocity);
}

void ShooterWheel::bangbang()
{
    if(abs(shooter_1.encoder.GetVelocity() > SHOOTER_WHEEL::SHOOTING_RPM - 2000))
        shooter_1.SetOpenLoopRampRate(0);
    else
        shooter_1.SetOpenLoopRampRate(6);

    if(abs(shooter_2.encoder.GetVelocity() > SHOOTER_WHEEL::SHOOTING_RPM - 2000))
        shooter_2.SetOpenLoopRampRate(0);
    else
        shooter_2.SetOpenLoopRampRate(6);


    if((abs(shooter_1.encoder.GetVelocity()) < SHOOTER_WHEEL::SHOOTING_RPM - 250))
        shooter_1.Set(-1);
    else
        shooter_1.Set(0);

    if((abs(shooter_2.encoder.GetVelocity()) < SHOOTER_WHEEL::SHOOTING_RPM - 250))
        shooter_2.Set(1);
    else
        shooter_2.Set(0);
}