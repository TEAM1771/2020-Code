#pragma once

/**
 * This is intended for controlling brushless motors
 * where the mechanism they're controlling has a
 * limited range of motion
 * 
 * The intention of this is to make it impossible to
 * tell it to go to a position outside of a range
 */

#include <numeric>
#include <rev\CANSparkMax.h>
#include <type_traits>

class PID_CANSparkMax : public rev::CANSparkMax
{
private:
    rev::CANPIDController pid_controller;

    double min_position = -std::numeric_limits<double>().infinity();
    double max_position = std::numeric_limits<double>().infinity();

    inline static rev::ControlType const default_control_type = rev::ControlType::kPosition;

public:
    rev::CANEncoder encoder;
    PID_CANSparkMax(int id, MotorType motor_type);

    // Sets motor to Zero if ouside range
    void Set(double) override;
    void SetVoltage(units::volt_t output) override;

    void           SetOutputRange(double min, double max);
    constexpr void SetPositionRange(double min, double max)
    {
        min_position = min;
        max_position = max;
    }

    [[deprecated]] rev::CANPIDController GetPIDController();

    /**
     * If the target is within the position range, it will go to the target
     * If not, it will go as close as it can to the target without exceding the range
     */
    void SetTarget(double target, rev::ControlType = default_control_type);

    rev::CANError SetP(double P);
    rev::CANError SetI(double I);
    rev::CANError SetD(double D);
    rev::CANError SetDFilter(double F);
    rev::CANError SetFF(double FF);
};
