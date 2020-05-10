#pragma once

#include "Constants.hpp"
#include "PID_CANSparkMax.hpp"

class ShooterWheel
{
    PID_CANSparkMax shooter_1 { SHOOTER_WHEEL::PORT_1, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    PID_CANSparkMax shooter_2 { SHOOTER_WHEEL::PORT_2, rev::CANSparkMaxLowLevel::MotorType::kBrushless };


public:
    ShooterWheel();

    [[deprecated]] void bangbang();
};
