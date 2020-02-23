#pragma once
#include "Constants.hpp"
#include <rev\CANSparkMax.h>
#include <frc\DigitalInput.h>

class Hopper
{
    rev::CANSparkMax hopperIndexerNeo {HOPP::hopperIndexerNeo};
    rev::CANSparkMax hopperTransportNeo {HOPP::hopperTransportNeo};

    public:
    bool isLaserBroken;
    int numberOfBalls;
    void transportBall();
    
    
}
