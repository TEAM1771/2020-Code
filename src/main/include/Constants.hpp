#pragma once

#include "JoystickButton.hpp"
#include <ctre/Phoenix.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>

using can_adr = unsigned;

namespace BUTTON
{
    inline frc::Joystick rStick { 0 },
        lStick { 1 },
        oStick { 2 };
    namespace INTAKE
    {
        inline JoystickButton DEPLOY { BUTTON::oStick, 3 };
        inline JoystickButton RETRACT { BUTTON::oStick, 4 };
        inline JoystickButton INTAKE { BUTTON::oStick, 5 };
    } // namespace INTAKE
    namespace SHOOTER
    {
        inline JoystickButton AIM_FRONT { BUTTON::oStick, 8 };
        inline JoystickButton AIM_BACK { BUTTON::oStick, 10 };
        inline JoystickButton AIM_SIDE { BUTTON::oStick, 2 };
        inline JoystickButton BATTERSHOT { BUTTON::oStick, 6 };
        inline JoystickButton SHOOT { BUTTON::oStick, 1 };
    } // namespace SHOOTER

    namespace CLIMBER
    {
        inline JoystickButton RAISE { BUTTON::lStick, 11 };
    }
} // namespace BUTTON

namespace TRANSMISSION
{
    constexpr can_adr RIGHT_MOTOR = 15;
    constexpr can_adr LEFT_MOTOR  = 17;

    constexpr auto IDLE_MODE = NeutralMode::Coast;

    constexpr can_adr SHIFTER = 0;

    constexpr int SHIFT_UP_POINT   = 16000;
    constexpr int SHIFT_DOWN_POINT = 6000;
} // namespace TRANSMISSION

namespace CAMERA
{
    constexpr double X_OFFSET = 4.2517710;
} // namespace CAMERA

namespace HOOD
{
    constexpr can_adr PORT = 7;

    constexpr auto IDLE_MODE = rev::CANSparkMax::IdleMode::kBrake;

    constexpr double P = 0.1;
    constexpr double I = 0.0;
    constexpr double D = 0.0;

    constexpr double MAX_SPEED = 0.8;

    enum class POSITION {
        BOTTOM       = 0,
        TRAVERSE     = -9,
        SAFE_TO_TURN = -42,
        MIDPOINT     = -26,
        BATTER       = -89
    };
} // namespace HOOD

namespace TURRET
{
    constexpr can_adr PORT = 6;

    constexpr auto IDLE_MODE = rev::CANSparkMax::IdleMode::kCoast;

    enum class POSITION {
        MAX_LEFT                  = -74,
        FRONT                     = -53,
        SAFE_TO_DEPLOY_HOOD_FRONT = -44,
        ZERO                      = 0,
        BACK                      = 53,
        MAX_RIGHT                 = 74
    };

    constexpr double TRAVERSE_SPEED = .7;

    constexpr double P = 0.1;
    constexpr double I = 0.0;
    constexpr double D = 0.0;

} // namespace TURRET

namespace SHOOTER_WHEEL
{
    constexpr can_adr PORT_1 = 4;
    constexpr can_adr PORT_2 = 5;

    constexpr auto IDLE_MODE = rev::CANSparkMax::IdleMode::kCoast;

    constexpr double SHOOTING_RPM = 8000;
} // namespace SHOOTER_WHEEL

namespace HOPPER
{
    namespace INDEXER
    {
        constexpr can_adr PORT = 10;
        constexpr double SPEED = 1;

        constexpr auto IDLE_MODE = rev::CANSparkMax::IdleMode::kBrake;
    } // namespace INDEXER

    namespace TRANSPORT
    {
        constexpr can_adr PORT = 10;

        constexpr auto IDLE_MODE = rev::CANSparkMax::IdleMode::kBrake;

        constexpr double SPEED       = 0.7;
        constexpr double SHOOT_SPEED = 1.0;

        constexpr double DISTANCE  = 73.0 / 3;
        constexpr double TOLERANCE = 0.1;

        constexpr double P = 0.3;
        constexpr double I = 0;
        constexpr double D = 0.0001;
    } // namespace TRANSPORT

    constexpr can_adr LIMIT_SWITCH = 0;

} // namespace HOPPER

namespace CLIMBER
{
    constexpr int PORT_1 = 47;
    constexpr int PORT_2 = 9;

    constexpr auto IDLE_MODE = rev::CANSparkMax::IdleMode::kBrake;

    constexpr double P = 0.1771;
    constexpr double I = 0.0;
    constexpr double D = 0.0;

    constexpr double MAX_OUTPUT = 1;

    enum class POSITION {
        DOWN = 100,
        UP   = 802,
        ZERO = 0
    };
} // namespace CLIMBER

namespace INTAKE
{
    constexpr can_adr PCM_PORT = 1;
    constexpr can_adr PORT     = 12;

    constexpr auto IDLE_MODE = rev::CANSparkMax::IdleMode::kCoast;

    enum class DIRECTION {
        OUT,
        OFF,
        IN
    };

    constexpr double IN_SPEED  = -1;
    constexpr double OUT_SPEED = 1;
} // namespace INTAKE
