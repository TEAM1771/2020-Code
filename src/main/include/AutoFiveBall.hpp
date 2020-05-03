#pragma once

#include "AutoBase.hpp"
#include "Constants.hpp"

// namespace FIVE_BALL_CONSTANTS
// {
//     using namespace std::literals::chrono_literals;

//     constexpr double PICKUP_DISTANCE = 115;
//     constexpr auto   TURN_TIME       = 0.2s;
//     constexpr auto   TIME_BACKWARD   = 1.5s;
// } // namespace FIVE_BALL_CONSTANTS

template <class Robot>
class AutoFiveBall : public AutoBase<Robot>
{
    using AutoBase<Robot>::robot;
    using AutoBase<Robot>::is_auto;


public:
    using AutoBase<Robot>::AutoBase;

    void init() override
    {
        using namespace FIVE_BALL_CONSTANTS;
        using namespace std::literals::chrono_literals;

        // Start BangBang and indexer
        std::thread run_shooter_wheel_and_index_balls = { [this] {
            using namespace std::literals::chrono_literals;
            while(is_auto())
            {
                robot->shooter_wheel.bangbang();
                robot->hopper.index(false);       // don't warn when called while shooting
                frc::Wait(.005);
                //std::this_thread::sleep_for(5ms); // don't spam the CAN network
            }
        } };

        // drive back / intake
        robot->intake.deploy(true);
        robot->intake.drive(INTAKE::DIRECTION::IN);
        while(robot->drivetrain.driveForwards(PICKUP_DISTANCE))
            frc::Wait(.02); // don't spam the CAN network
        // turn
        robot->drivetrain.drive(.3, 0);
        std::this_thread::sleep_for(TURN_TIME);
        // drive forward and target back, shoot when ready
        robot->drivetrain.drive(.5, .5);
        std::thread aim_and_shoot { [this] {
            robot->limelight.setLEDMode(LimeLight::LED_Mode::Force_On);
            while(is_auto())
            {
                std::this_thread::sleep_for(10ms);
                if(robot->aim(TURRET::POSITION::BACK))
                    robot->hopper.shoot();
            }
        } };
        std::this_thread::sleep_for(TIME_BACKWARD);
        robot->drivetrain.drive(0, 0);

        // wait for threads to exit
        run_shooter_wheel_and_index_balls.join();
        aim_and_shoot.join();
    }
};
