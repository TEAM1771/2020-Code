#include "Robot.hpp"

Robot::Robot()
{

}

void Robot::AutonomousInit()
{

}

void Robot::AutonomousPeriodic() 
{

}

void Robot::TeleopInit()
{

}

void Robot::TeleopPeriodic()
{
  drive.drive(lStick.GetY(), rStick.GetY());
}

void Robot::TestPeriodic()
{

}

void Robot::IntakeManager()
{
  // Intake down

  intake.deploy(oStick.GetRawButton(INTAKE::BUTTONS::intakedown));
 
  // Intake in
  intake.intakeneo.set(oStick.GetRawButton(INTAKE::BUTTONS::intakein));
  // Intake out 
  intake.intakeneo.set(oStick.GetRawButton(INTAKE::BUTTONS::intakeout));
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
