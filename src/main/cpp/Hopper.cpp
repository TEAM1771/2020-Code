#include "Hopper.hpp"
#include <iostream>

Hopper::Hopper()
{
    indexerNeo.Set(HOPPER::INDEXER::SPEED);
    indexerNeo.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    transportNeo.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    numberOfBalls = 3;
    hopperPIDController.SetP(HOPPER::TRANSPORT::P);
    hopperPIDController.SetI(HOPPER::TRANSPORT::I);
    hopperPIDController.SetD(HOPPER::TRANSPORT::D);
    hopperPIDController.SetFeedbackDevice(transportEncoder);
    hopperPIDController.SetOutputRange(-1,1);
    transportEncoder.SetPosition(0);
    targetDistance = HOPPER::TRANSPORT::DISTANCE; //Because there is no set distance for the PID, only position, we will have to always update the target by adding the desired movement distance  
}

void Hopper::driveDistance()
{

    hopperPIDController.SetReference(targetDistance,rev::ControlType::kPosition);
    if( valueInRange(transportEncoder.GetPosition(), HOPPER::TRANSPORT::DISTANCE -.5, HOPPER::TRANSPORT::DISTANCE + 0.5) ) //Ball has traveled distance, update new target position for next ball
    {
        targetDistance = transportEncoder.GetPosition() + HOPPER::TRANSPORT::DISTANCE;
        numberOfBalls++;
    }

        
}

bool Hopper::valueInRange(double value, double min, double max)
{
    if ( (value >= min) && (value <= max) )
    {
         return true;
    }
    else
    {
        return false;
    }
    
}

void Hopper::giveStatus()
{
    std::cout << "Hopper encoder: " << transportEncoder.GetPosition() << std::endl;
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
    transportEncoder.SetPosition(0);
    numberOfBalls = 0;
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
    if (isLaserBroken() && numberOfBalls < 3 && isRunning == false) {
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

void Hopper::controlFeedPID()
{
    static bool isRunning = false;
    if (isLaserBroken() && numberOfBalls < 3 && !isRunning)
    {
        stopIndexer();
        driveDistance();
        isRunning = true;
    }
    else if(!isLaserBroken() && numberOfBalls < 4)
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