#include "Hood.hpp"

#include <cmath>
#include <vector>
#include <algorithm>

Hood::Hood(LimeLight const& limelight):
    limelight_ { limelight }
{
    hood_.RestoreFactoryDefaults();
    hood_.SetIdleMode(HOOD::IDLE_MODE);
    
    pidController_.SetP(HOOD::P);
    pidController_.SetI(HOOD::I);
    pidController_.SetD(HOOD::D);

    pidController_.SetFeedbackDevice(encoder_);
    pidController_.SetReference(static_cast<double>(HOOD::POSITION::BOTTOM), rev::ControlType::kPosition);
    pidController_.SetOutputRange(-HOOD::MAX_SPEED, HOOD::MAX_SPEED);
}

bool Hood::goToPosition(HOOD::POSITION position, double tolerance)
{
    if(position != position_)
    {
        pidController_.SetReference(static_cast<double>(position), rev::ControlType::kPosition);
        position_ = position;
    }
    return std::fabs(encoder_.GetPosition() - static_cast<double>(position)) < tolerance;
}

struct table_row
{
    double y_val;
    double hood_val;
};

[[nodiscard]] inline static double getTrackingValue(double yval)
{
    constexpr table_row lookup_table[] {
        { 20.0104, -13.1929 },
        { 10.4538, -17.0433 },
        { 1.97857, -21.3750 },
        {-3.02635, -22.0117 },
        {-5.88120, -21.6297 },
        {-9.15754, -21.3750 }
    };

    // finds the correct interpolation range
    auto const range = std::prev(std::find_if(std::next(std::begin(lookup_table)), std::prev(std::end(lookup_table)), [=](auto const& val) {
        return yval >= val.y_val;
    }));

    // preforms the interpolation and limits output range to values that wont damage the hood
    return std::clamp(((range->hood_val - std::next(range)->hood_val)
            / (range->y_val - std::next(range)->y_val))
            * (yval - std::next(range)->y_val)
            + std::next(range)->hood_val,
            static_cast<double>(HOOD::POSITION::SAFE_TO_TURN), 
            static_cast<double>(HOOD::POSITION::TRAVERSE));
}

bool Hood::visionTrack(double tolerance)
{
    if(limelight_.hasTarget())
    {
        double const target = getTrackingValue(limelight_.getY());
        pidController_.SetReference(target, rev::ControlType::kPosition);
        return std::fabs(target - encoder_.GetPosition()) < tolerance;
    }
    else
    {
        goToPosition(HOOD::POSITION::TRAVERSE);
        return false;        
    }
    
}

[[nodiscard]] constexpr double scaleOutput(double inputMin, double inputMax, double outputMin, double outputMax, double input)
{
   return ( (input - inputMin) / (inputMax - inputMin) ) * ( ( outputMax - outputMin) ) + inputMin; 
}

void Hood::manualPositionControl(double position)
{
    pidController_.SetReference(scaleOutput(
        0,
        1, 
        static_cast<double>(HOOD::POSITION::TRAVERSE),
        static_cast<double>(HOOD::POSITION::SAFE_TO_TURN), 
        std::clamp(position,0.0,1.0)
        ), rev::ControlType::kPosition);
}
