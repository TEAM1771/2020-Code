#pragma once

#include "Constants.hpp"
#include "LimeLight.hpp"
#include "PID_CANSparkMax.hpp"

class Turret
{
    LimeLight const& limelight_;

    PID_CANSparkMax turretTurnyTurny_ { TURRET::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless };

    TURRET::POSITION position_ = TURRET::POSITION::ZERO;
    bool             tracking_ = false;

    struct visionState
    {
        bool isTracking;
        bool readyToShoot;
    };

public:
    explicit Turret(LimeLight const& limelight);

    /// returns true if tolerance is met
    bool goToPosition(TURRET::POSITION position, double tolerance = 0.01);

    /// goes to position and then starts tracking, returns true if tolerance is met
    visionState visionTrack(TURRET::POSITION initPosition, double tolerance = 0.01);

    /// used for tuning interpolation tables
    void manualPositionControl(double position);
};
