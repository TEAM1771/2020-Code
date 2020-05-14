#pragma once

#include "AutoBase.hpp"
#include "Constants.hpp"
#include <frc/Timer.h>

template <class Robot>
class AutoSimple : public AutoBase<Robot>
{
    using AutoBase<Robot>::robot;

    frc::Timer timer;

    double const wait_time = 10;

public:
    using AutoBase<Robot>::AutoBase;

    void init() override
    {
        timer.Reset();
        timer.Start();

        robot->intake.deploy(true);
    }

    void run() override
    {
        robot->shooter_wheel.bangbang();
        if(!robot->drivetrain.driveDistanceForward(2))
        {
            if(auto [is_tracking, readyToShoot] = robot->turret.visionTrack(TURRET::POSITION::FRONT); is_tracking)
            {
                if(robot->hood.visionTrack() && readyToShoot && timer.Get() > wait_time)
                    robot->hopper.shoot();
            }
            else
                robot->hood.goToPosition(HOOD::POSITION::TRAVERSE);
        }
    }
};