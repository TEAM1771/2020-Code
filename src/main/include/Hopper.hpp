#pragma once
#include "Constants.hpp"
#include <frc/Timer.h>
#include <frc\DigitalInput.h>
#include <rev\CANSparkMax.h>
class Hopper
{
    rev::CANSparkMax      indexerNeo { HOPPER::INDEXER::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax      transportNeo { HOPPER::TRANSPORT::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    frc::Timer            timer;
    frc::DigitalInput     beamBreak { HOPPER::laserPort };
    rev::CANPIDController hopperPIDController = transportNeo.GetPIDController();
    rev::CANEncoder       transportEncoder    = transportNeo.GetEncoder();

public:
    static double timeElapsed;
    int           numberOfBalls = 3;
    double        targetDistance;

    Hopper();
    bool isLaserBroken() const;
    //static bool hasDrivenDistance();
    void transportBall();
    void feedShooter();
    void stopFeed();
    void controlFeed();
    void startIndexer();
    void stopIndexer();
    void manualIndexerControl(double speed);
    void manualTransportControl(double speed);
    void checkBallProgress();
    void driveDistance();
    void giveStatus();
    void controlFeedPID();

    bool valueInRange(double value, double min, double max);
};
