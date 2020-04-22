#include "Turret.hpp"
Turret::Turret(LimeLight const& limelight):
    limelight_ { limelight }
{
    turretTurnyTurny_.RestoreFactoryDefaults();
    
    turretTurnyTurny_.SetIdleMode(TURRET::IDLE_MODE);
    
    pidController_.SetP(TURRET::P);
    pidController_.SetI(TURRET::I);
    pidController_.SetD(TURRET::D);
    
    pidController_.SetFeedbackDevice(encoder_);

    pidController_.SetReference(static_cast<double>(TURRET::POSITION::ZERO), rev::ControlType::kPosition);
    pidController_.SetOutputRange(-TURRET::TRAVERSE_SPEED, TURRET::TRAVERSE_SPEED);
}

bool Turret::goToPosition(TURRET::POSITION position, double tolerance)
{
    if(position != position_)
    {
        pidController_.SetReference(static_cast<double>(position), rev::ControlType::kPosition);
        position_ = position;
    }

    tracking_ = false; // Reset for Turret::visionTrack(...)

    return std::fabs(encoder_.GetPosition() - static_cast<double>(position)) < tolerance;
}

Turret::visionState Turret::visionTrack(TURRET::POSITION initPosition, double tolerance)
{
    if(!tracking_) // move to initPosition
    {
        tracking_ = goToPosition(initPosition);
        return {false, false};
    }
    
    if (limelight_.hasTarget())
    {
        double const xOffset = limelight_.getX() + CAMERA::X_OFFSET;
        double const output = xOffset/35;
        double const currentTicks = encoder_.GetPosition();
        if (currentTicks < static_cast<double>(TURRET::POSITION::MAX_RIGHT) 
         && currentTicks > static_cast<double>(TURRET::POSITION::MAX_LEFT))
            turretTurnyTurny_.Set(output);
        else
            turretTurnyTurny_.Set(0);
        return { true, fabs(xOffset) < tolerance };
    }
    turretTurnyTurny_.Set(0);
    return {false, false};
}

[[nodiscard]] constexpr double scaleOutput(double inputMin, double inputMax, double outputMin, double outputMax, double input)
{
   return ( (input - inputMin) / (inputMax - inputMin) ) * ( ( outputMax - outputMin) ) + inputMin; 
}

void Turret::manualPositionControl(double position)
{
    pidController_.SetReference(scaleOutput(
       -1,
        1, 
        static_cast<double>(TURRET::POSITION::MAX_LEFT),
        static_cast<double>(TURRET::POSITION::MAX_RIGHT), 
        std::clamp(position,-1.0,1.0)
        ), rev::ControlType::kPosition);
}
