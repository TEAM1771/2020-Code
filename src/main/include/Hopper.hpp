#pragma once
#include "Constants.hpp"
#include <rev\CANSparkMax.h>
#include <frc\DigitalInput.h>
#include <frc/Timer.h>
class Hopper
{
    rev::CANSparkMax indexerNeo {HOPP::hopperIndexerNeo, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax transportNeo {HOPP::hopperTransportNeo, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    frc::Timer timer;
    frc::DigitalInput beamBreak {HOPP::laserPort};
public:
    Hopper();
    bool isLaserBroken() const;
    int numberOfBalls = 3;
    static double timeElapsed;
    void transportBall();
    void feedShooter();
    void stopFeed();
    void controlFeed();
    void startIndexer();
    void stopIndexer();
    void manualIndexerControl(double speed);
    void manualTransportControl(double speed);
    void checkBallProgress();
};