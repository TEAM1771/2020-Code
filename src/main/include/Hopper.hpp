#pragma once

#include <frc/DigitalInput.h>
#include "Constants.hpp"

class Hopper 
{
    rev::CANSparkMax indexer   { HOPPER::INDEXER::PORT,   rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax transport { HOPPER::TRANSPORT::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    
    rev::CANPIDController pidController = transport.GetPIDController();
    rev::CANEncoder encoder = transport.GetEncoder();
    
    frc::DigitalInput limitSwitch { HOPPER::LIMIT_SWITCH };
    
    int numberOfBalls = 3;
    double targetDistance = HOPPER::TRANSPORT::DISTANCE;
    bool isTransporting = false;
    bool invalidStopFlag = false;

    void driveDistance();
public:
    Hopper();
    void index();
    void shoot(); // must call Hopper::stop() to stop shooting
    void stop();
};
