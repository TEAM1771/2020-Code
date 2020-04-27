#include "Robot.hpp"
#include <frc/Timer.h>

void Robot::AutonomousInit()
{
    auton->init();
}

void Robot::AutonomousPeriodic()
{
    auton->run();
}

void Robot::TeleopInit()
{
    hopper.stop(); // eliminates need to shoot at start of teleop
}

void Robot::TeleopPeriodic()
{
    shooter_wheel.bangbang();
    ButtonManager();
}

void Robot::TestPeriodic()
{
}

void Robot::DisabledInit()
{
}

void Robot::DisabledPeriodic()
{
}

void Robot::ButtonManager()
{
    bool targetLocked = false;
    bool deployIntake = false;
    if(BUTTON::SHOOTER::AIM_FRONT)
    {
        deployIntake = true;
        if(auto [is_tracking, readyToShoot] = turret.visionTrack(TURRET::POSITION::FRONT); is_tracking)
            targetLocked = hood.visionTrack() && readyToShoot;
        else
            hood.goToPosition(HOOD::POSITION::TRAVERSE);
    }
    else if(BUTTON::SHOOTER::AIM_BACK)
    {
        deployIntake = true;
        if(auto [is_tracking, readyToShoot] = turret.visionTrack(TURRET::POSITION::BACK); is_tracking)
            targetLocked = hood.visionTrack() && readyToShoot;
        else
            hood.goToPosition(HOOD::POSITION::TRAVERSE);
    }
    else if(BUTTON::SHOOTER::BATTERSHOT)
    {
        deployIntake             = true;
        bool const turret_in_pos = turret.goToPosition(TURRET::POSITION::FRONT,
                                                       fabs(static_cast<double>(TURRET::POSITION::FRONT) - static_cast<double>(TURRET::POSITION::SAFE_TO_DEPLOY_HOOD_FRONT)));
        if(turret_in_pos)
            targetLocked = hood.goToPosition(HOOD::POSITION::BATTER);
        else
            hood.goToPosition(HOOD::POSITION::TRAVERSE);
    }
    else if(BUTTON::SHOOTER::AIM_SIDE)
    {
        deployIntake = true;
        targetLocked = hood.goToPosition(HOOD::POSITION::MIDPOINT);
    }
    else
    {
        deployIntake = false;
        if(hood.goToPosition(HOOD::POSITION::BOTTOM, fabs(static_cast<double>(HOOD::POSITION::SAFE_TO_TURN))))
            turret.goToPosition(TURRET::POSITION::ZERO);
    }

    intake.deploy(BUTTON::INTAKE::DEPLOY || deployIntake);

    if(BUTTON::SHOOTER::SHOOT.getRawButtonReleased())
        hopper.stop();
    if(targetLocked && BUTTON::SHOOTER::SHOOT)
        hopper.shoot();
    else if(! BUTTON::SHOOTER::SHOOT)
        hopper.index();

    if(BUTTON::INTAKE::INTAKE)
        intake.drive(INTAKE::DIRECTION::IN);
    else if(BUTTON::INTAKE::RETRACT)
        intake.drive(INTAKE::DIRECTION::OUT);
    else
        intake.drive(INTAKE::DIRECTION::OFF);

    climber.ButtonManager();
}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif
