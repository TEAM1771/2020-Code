
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/livewindow/LiveWindow.h>

class Turret
{

public:

    //  shooter neos
    rev::CANSparkMax shooterneo1 {TURRET::shooterneo1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax shooterneo2 {TURRET::shooterneo2, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    //  turret ring neo
    rev::CANSparkMax turretneo {TURRET::turretneo, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    //  hood neo
    rev::CANSparkMax hoodneo {TURRET::hoodneo, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

}