#include "Climber.hpp"
#include "Constants.hpp"

Climber::Climber()
{
    climber_1.RestoreFactoryDefaults();
    climber_2.RestoreFactoryDefaults();

    climber_1.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    climber_2.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    climber_1_pidController.SetP(CLIMBER::P);
    climber_1_pidController.SetI(CLIMBER::I);
    climber_1_pidController.SetD(CLIMBER::D);
    climber_1_pidController.SetFeedbackDevice(climber_1_encoder);
    climber_1_pidController.SetReference(CLIMBER::POSITIONS::DOWN, rev::ControlType::kPosition);
    climber_1_pidController.SetOutputRange(-CLIMBER::MAX_OUTPUT, CLIMBER::MAX_OUTPUT);
    
    climber_2.Follow(climber_1, true);
}

void Climber::climb(bool val)
{
    climber_1_pidController.SetReference(val?CLIMBER::POSITIONS::UP : CLIMBER::POSITIONS::DOWN, rev::ControlType::kPosition);
    //climber_2_pidController.SetReference(val?CLIMBER::POSITIONS::UP : CLIMBER::POSITIONS::DOWN, rev::ControlType::kPosition);
}