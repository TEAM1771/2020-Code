#pragma once

#include "Constants.hpp"
#include "LimeLight.hpp"
#include <PID_CANSparkMax.hpp>
#include <frc/Joystick.h>

class Hood
{
    LimeLight const& limelight_;

    PID_CANSparkMax hood_ { HOOD::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless };

    HOOD::POSITION position_ = HOOD::POSITION::BOTTOM;

public:
    explicit Hood(LimeLight const& limelight);

    /// returns true if tolerance is met
    bool goToPosition(HOOD::POSITION position, double tolerance = 1);

    /// returns true if tolerance is met
    bool visionTrack(double tolerance = 1);

    /// used for tuning interpolation tables
    void manualPositionControl(double position);
};
