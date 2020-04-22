#pragma once

#include <frc/Timer.h>

#include "AutoBase.hpp"
#include "Constants.hpp"

template<class Robot>
class AutoFiveBall : public AutoBase<Robot>
{
    using AutoBase<Robot>::robot;
    enum class Stage {
        PickUpBalls,
        Turn,
        DriveBack,
        Shoot
    } stage;
    frc::Timer timer;

    double const pickup_distance = 115;

public:
    using AutoBase<Robot>::AutoBase;
    
    void init() override
    {
        timer.Reset();
        timer.Start();
    }

    void run() override
    {
        switch (stage)
        {
        case Stage::PickUpBalls:
        {
            if(! robot->drivetrain.driveDistanceForward(pickup_distance))
                stage = AutoFiveBall::Stage::Turn;
            else break;
        } [[fallthrough]];
        
        case Stage::Turn:
            break;
        default:
            break;
        }
    }
};
