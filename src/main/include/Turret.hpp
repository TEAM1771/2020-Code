
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/livewindow/LiveWindow.h>

class Turret
{

    //  shooter neos
    rev::CANSparkMax shooter_1 {SHOOTER::TURRET::PORT_1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax shooter_2 {SHOOTER::TURRET::PORT_2, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    //  turret ring neo
    rev::CANSparkMax turret {SHOOTER::TURRET::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    //  hood neo
    rev::CANSparkMax hood {SHOOTER::TURRET::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
public:
    Turret();

}