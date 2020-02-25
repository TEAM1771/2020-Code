#include "Hopper.hpp"
#include <iostream>

Hopper::Hopper()
{
    indexerNeo.Set(HOPP::hopperIndexerForward);
    indexerNeo.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    transportNeo.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

bool Hopper::isLaserBroken() const
{
    return beamBreak.Get();
}

void Hopper::transportBall()
{
     transportNeo.Set(HOPP::hopperTransportForward); 
}
void Hopper::feedShooter()
{
    transportNeo.Set(HOPP::hopperFeedForward);
}
void Hopper::stopFeed()
{
    transportNeo.Set(0);
    numberOfBalls = 0;
}
void Hopper::startIndexer()
{
    indexerNeo.Set(HOPP::hopperIndexerForward);
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
    if (isLaserBroken() && numberOfBalls < 5 && isRunning == false) {
        stopIndexer();
        transportBall();
        timer.Reset();
        timer.Start();
        std::cout << "OMG THE LASER IS BROKEN" << '\n';
        isRunning = true;
    }
    else if (!isLaserBroken())
    {
        startIndexer();
        isRunning = false;
    }
    
    
}

void Hopper::checkBallProgress()
{
    if ( timer.HasPeriodPassed(HOPP::hopperTimer) )
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