#include "Turret.hpp"
#include <cmath>
Turret::Turret(LimeLight const& limelight)
    : limelight_ { limelight }
{
    turretTurnyTurny_.RestoreFactoryDefaults();

    turretTurnyTurny_.SetIdleMode(TURRET::IDLE_MODE);

    turretTurnyTurny_.SetP(TURRET::P);
    turretTurnyTurny_.SetI(TURRET::I);
    turretTurnyTurny_.SetD(TURRET::D);

    turretTurnyTurny_.SetTarget(TURRET::POSITION::ZERO);
    turretTurnyTurny_.SetOutputRange(-TURRET::TRAVERSE_SPEED, TURRET::TRAVERSE_SPEED);
    turretTurnyTurny_.SetPositionRange(TURRET::POSITION::MAX_LEFT, TURRET::POSITION::MAX_RIGHT);
}

bool Turret::goToPosition(TURRET::POSITION position, double tolerance)
{
    if(position != position_)
    {
        turretTurnyTurny_.SetTarget(position);
        position_ = position;
    }

    tracking_ = false; // Reset for Turret::visionTrack(...)

    return std::fabs(turretTurnyTurny_.encoder.GetPosition() - position) < tolerance;
}

Turret::visionState Turret::visionTrack(TURRET::POSITION initPosition, double tolerance)
{
    if(! tracking_) // move to initPosition
    {
        tracking_ = goToPosition(initPosition);
        return { false, false };
    }

    if(limelight_.hasTarget())
    {
        double const xOffset = limelight_.getX() + CAMERA::X_OFFSET;
        double const output  = xOffset / 35;
        turretTurnyTurny_.Set(output);
        return { true, fabs(xOffset) < tolerance };
    }
    turretTurnyTurny_.Set(0);
    return { false, false };
}

Turret::visionState Turret::visionTrack_v2(TURRET::POSITION initPosition, double tolerance)
{
    if(! tracking_) // move to initPosition
    {
        tracking_ = goToPosition(initPosition);
        return { false, false };
    }

    if(limelight_.hasTarget())
    {
        double const xOffsetDeg = limelight_.getX() + CAMERA::X_OFFSET;
        double const xOffsetRad = xOffsetDeg * 2 * pi / 180;
        double const xOffset    = xOffsetRad * TURRET::TICKS_PER_RADIAN;

        double const xPosition = turretTurnyTurny_.encoder.GetPosition();
        double const xTarget   = xPosition + xOffset;

        static double prevOffsetDeg = 0;
        if(prevOffsetDeg == xOffsetDeg) // prevents reusing outdated data
        {
            std::cout << "cam data reused\n";              // remove this section if this doesn't appear in the output, if it does appear remove this print statment
            return { true, fabs(xOffsetDeg) < tolerance }; // maybe unnecissary, idk
        }
        prevOffsetDeg = xOffsetDeg;

        // for testing, this should print a constant or near constant value when the robot is stationary
        // the value should change when the robot moves
        std::cout << "xTarget: " << xTarget << "\n";
        turretTurnyTurny_.Set(0);
        //turretTurnyTurny_.SetTarget(xTarget);

        return { true, fabs(xOffsetDeg) < tolerance };
    }

    return { false, false };
}

void Turret::manualPositionControl(double position)
{
    turretTurnyTurny_.SetTarget(ngr::scaleOutput(
                                    -1,
                                    1,
                                    TURRET::POSITION::MAX_LEFT,
                                    TURRET::POSITION::MAX_RIGHT,
                                    std::clamp(position, -1.0, 1.0)),
                                rev::ControlType::kPosition);
}
