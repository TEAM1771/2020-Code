#pragma once

#include "Constants.hpp"
#include "LimeLight.hpp"
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>

class Hood
{
    LimeLight const& limelight_;

    rev::CANSparkMax      hood_ { HOOD::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANPIDController pidController_ = hood_.GetPIDController();
    rev::CANEncoder       encoder_       = hood_.GetEncoder();

    HOOD::POSITION position_ = HOOD::POSITION::BOTTOM;

public:
    explicit Hood(LimeLight const& limelight);

    /// returns true if tolerance is met
    bool goToPosition(HOOD::POSITION position, double tolerance = 0.01);

    /// returns true if tolerance is met
    bool visionTrack(double tolerance = 0.01);

    /// used for tuning interpolation tables
    void manualPositionControl(double position);
};
