#include "Hopper.hpp"
#include <iostream>

Hopper::Hopper()
{
    indexerNeo.Set(HOPPER::INDEXER::SPEED);
    indexerNeo.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    transportNeo.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    numberOfBalls = 3;
}

bool Hopper::isLaserBroken() const
{
    return !beamBreak.Get();
}

void Hopper::transportBall()
{
     transportNeo.Set(HOPPER::TRANSPORT::SPEED); 
}
void Hopper::feedShooter()
{
    transportNeo.Set(HOPPER::TRANSPORT::SHOOT_SPEED);
}
void Hopper::stopFeed()
{
    transportNeo.Set(0);
    numberOfBalls = 0;
}
void Hopper::startIndexer()
{
    indexerNeo.Set(HOPPER::INDEXER::SPEED);
}
void Hopper::stopIndexer()
{
    indexerNeo.Set(0);
}
//controlFeed should make the decision to feed a ball into the transport
void Hopper::controlFeed()
{   
    static bool isRunning = false;
    checkBallProgress();
    if (isLaserBroken() && numberOfBalls < 4 && isRunning == false) {
        stopIndexer();
        transportBall();
        timer.Reset();
        timer.Start();
        std::cout << "OMG THE LASER IS BROKEN" << '\n';
        isRunning = true;
    }
    else if (!isLaserBroken() && numberOfBalls < 4)
    {
        startIndexer();
        isRunning = false;
    }
    else
    {
        stopIndexer();
        isRunning = false;
    }
    
    
    
}

void Hopper::checkBallProgress()
{
    if ( timer.HasPeriodPassed(HOPPER::hopperTimer) )
    {
        timer.Stop();
        timer.Reset();
        transportNeo.Set(0);
        numberOfBalls++;
    }
}

void Hopper::manualIndexerControl(double speed)
{
    indexerNeo.Set(speed);
}

void Hopper::manualTransportControl(double speed)
{
    transportNeo.Set(speed);
}