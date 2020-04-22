#include "Hopper.hpp"

Hopper::Hopper() 
{
    indexer.Set(HOPPER::INDEXER::SPEED);

    indexer.SetIdleMode(HOPPER::INDEXER::IDLE_MODE);
    transport.SetIdleMode(HOPPER::TRANSPORT::IDLE_MODE);
    
    pidController.SetP(HOPPER::TRANSPORT::P);
    pidController.SetI(HOPPER::TRANSPORT::I);
    pidController.SetD(HOPPER::TRANSPORT::D);

    pidController.SetFeedbackDevice(encoder);
    pidController.SetOutputRange(-HOPPER::TRANSPORT::SPEED, HOPPER::TRANSPORT::SPEED);

    encoder.SetPosition(0);
}


void Hopper::index()
{
    if(invalidStopFlag)
    {
        std::cerr << "Stop not called after shooting: Indexer Aborting\n";
        return;
    }

    if (limitSwitch.Get() && numberOfBalls < 3 && !isTransporting)
    {
        pidController.SetReference(targetDistance, rev::ControlType::kPosition);
        numberOfBalls++;
        isTransporting = true;
    }

    if(isTransporting && encoder.GetPosition() > (targetDistance - HOPPER::TRANSPORT::TOLERANCE))
    {
        targetDistance += HOPPER::TRANSPORT::DISTANCE;
        isTransporting = false;
    }
    
    if(!limitSwitch.Get() && numberOfBalls < 4)
        indexer.Set(HOPPER::INDEXER::SPEED);
    else
        indexer.Set(0);

}

void Hopper::shoot()
{
    invalidStopFlag = true;
    indexer.Set(HOPPER::INDEXER::SPEED);
    transport.Set(HOPPER::TRANSPORT::SHOOT_SPEED);
}

void Hopper::stop()
{
    invalidStopFlag = false;
    numberOfBalls = 0;
    targetDistance = HOPPER::TRANSPORT::DISTANCE;
    isTransporting = false;
    encoder.SetPosition(0);

    indexer.Set(0);
    transport.Set(0);
}