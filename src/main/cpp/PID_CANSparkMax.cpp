#include "PID_CANSparkMax.hpp"
#include "Constants.hpp"

PID_CANSparkMax::PID_CANSparkMax(int id, MotorType motor_type)
    : rev::CANSparkMax(id, motor_type)
    , pid_controller { rev::CANSparkMax::GetPIDController() }
    , encoder { GetEncoder() }
{
    pid_controller.SetFeedbackDevice(encoder);
}

void PID_CANSparkMax::Set(double value)
{
    if(ngr::value_in_range(encoder.GetPosition(), min_position, max_position))
        rev::CANSparkMax::Set(value);
    else
        rev::CANSparkMax::Set(0);
}

void PID_CANSparkMax::SetVoltage(units::volt_t value)
{
    if(ngr::value_in_range(encoder.GetPosition(), min_position, max_position))
        rev::CANSparkMax::SetVoltage(value);
    else
        rev::CANSparkMax::Set(0);
}

void PID_CANSparkMax::SetOutputRange(double min, double max)
{
    if(min >= max)
        std::cerr << "Invalid Output Range: min: " << min << "\tmax: " << max << '\n';
    pid_controller.SetOutputRange(min, max);
}

void PID_CANSparkMax::SetTarget(double position, rev::ControlType control_type)
{
    pid_controller.SetReference(std::clamp(position, min_position, max_position), control_type);
}

rev::CANError PID_CANSparkMax::SetP(double P) { return pid_controller.SetP(P); }
rev::CANError PID_CANSparkMax::SetI(double I) { return pid_controller.SetI(I); }
rev::CANError PID_CANSparkMax::SetD(double D) { return pid_controller.SetD(D); }
rev::CANError PID_CANSparkMax::SetDFilter(double F) { return pid_controller.SetDFilter(F); }
rev::CANError PID_CANSparkMax::SetFF(double FF) { return pid_controller.SetFF(FF); }

rev::CANPIDController PID_CANSparkMax::GetPIDController()
{
    return rev::CANSparkMax::GetPIDController();
}