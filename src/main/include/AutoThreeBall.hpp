#pragma once

#include "AutoBase.hpp"
#include "Constants.hpp"
#include "Timer.hpp"

template <class Robot>
class AutoThreeBall : public AutoBase<Robot>
{
    using AutoBase<Robot>::robot;

    ngr::Timer timer;

public:
    using AutoBase<Robot>::AutoBase;

    void init() override
    {
        using namespace AUTO::THREE_BALL;

        timer.Reset();
        timer.Start();

        robot->intake.deploy(true);

        robot->limelight.setLEDMode(LimeLight::LED_Mode::Force_On);
    }

    void run() override
    {
        while(is_auto())
        {
            robot->shooter_wheel.bangbang();

            robot->drivetrain.reset();
            if(! robot->drivetrain.driveDistanceForward(DRIVE_DISTANCE))
                robot->aim(TURRET::POSITION::BACK);
            else if(robot->aim(TURRET::POSITION::BACK) && timer.Get() > MINIMUM_SHOOT_TIME)
                robot->hopper.shoot();
        }
    };