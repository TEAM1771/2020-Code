#pragma once

#include <rev\CANSparkMax.h>
#include "Constants.hpp"

class Climber
{
    rev::CANSparkMax climber_1 { CLIMBER::PORT_1, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax climber_2 { CLIMBER::PORT_2, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    
    rev::CANPIDController climber_1_pidController = climber_1.GetPIDController();
    rev::CANEncoder  climber_1_encoder = climber_1.GetEncoder();

    rev::CANPIDController climber_2_pidController = climber_2.GetPIDController();
    rev::CANEncoder climber_2_encoder = climber_2.GetEncoder();

public:
    Climber();

    void set(CLIMBER::POSITION position);

    void joystickControl(double);

    void printStatus();
};