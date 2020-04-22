#include "Climber.hpp"
#include "Constants.hpp"

Climber::Climber()
{
    climber_1.RestoreFactoryDefaults();
    climber_2.RestoreFactoryDefaults();

    climber_1.SetIdleMode(CLIMBER::IDLE_MODE);
    climber_2.SetIdleMode(CLIMBER::IDLE_MODE);

    climber_1_pidController.SetP(CLIMBER::P);
    climber_1_pidController.SetI(CLIMBER::I);
    climber_1_pidController.SetD(CLIMBER::D);
    climber_1_pidController.SetFeedbackDevice(climber_1_encoder);
    climber_1_pidController.SetReference(static_cast<double>(CLIMBER::POSITION::ZERO), rev::ControlType::kPosition);
    climber_1_pidController.SetOutputRange(-static_cast<double>(CLIMBER::MAX_OUTPUT), static_cast<double>(CLIMBER::MAX_OUTPUT));

    climber_2_pidController.SetP(CLIMBER::P);
    climber_2_pidController.SetI(CLIMBER::I);
    climber_2_pidController.SetD(CLIMBER::D);
    climber_2_pidController.SetFeedbackDevice(climber_2_encoder);
    climber_2_pidController.SetReference(static_cast<double>(CLIMBER::POSITION::ZERO), rev::ControlType::kPosition);
    climber_2_pidController.SetOutputRange(-static_cast<double>(CLIMBER::MAX_OUTPUT), static_cast<double>(CLIMBER::MAX_OUTPUT));
}

void Climber::set(CLIMBER::POSITION position)
{
    climber_1_pidController.SetReference(static_cast<double>(position), rev::ControlType::kPosition);
    climber_2_pidController.SetReference(-static_cast<double>(position), rev::ControlType::kPosition);
}

void Climber::joystickControl(double val)
{
    climber_1.Set(val);
    climber_2.Set(-val);
    printStatus();
}

void Climber::printStatus()
{
    std::cout<< "Climber 1: " << climber_1_encoder.GetPosition() << std::endl;
    std::cout<< "Climber 2: " << climber_2_encoder.GetPosition() << std::endl;
}