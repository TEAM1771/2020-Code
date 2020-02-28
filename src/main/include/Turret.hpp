
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/livewindow/LiveWindow.h>
#include <rev\CANSparkMax.h>
#include "Constants.hpp"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

class Turret
{

    //  shooter neos
    rev::CANSparkMax shooter_1 {SHOOTER::WHEEL::PORT_1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax shooter_2 {SHOOTER::WHEEL::PORT_2, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    //  turret ring neo
    rev::CANSparkMax turretTurnyTurny {SHOOTER::TURRET::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    //  hood neo
    rev::CANSparkMax hood {SHOOTER::HOOD::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};


    rev::CANPIDController shooter_pidController = shooter_1.GetPIDController();
    rev::CANEncoder shooter_encoder = shooter_1.GetEncoder();

    rev::CANPIDController turretTurnyTurny_pidController = turretTurnyTurny.GetPIDController();
    rev::CANEncoder turretTurnyTurny_encoder = turretTurnyTurny.GetEncoder();

    rev::CANPIDController hood_pidController = hood.GetPIDController();
    rev::CANEncoder hood_encoder = turretTurnyTurny.GetEncoder();

    int turnyturnyEncoderTicks;
    double cameraXValue;
    double cameraYValue;
    double cameraArea;
    bool cameraHasTarget;
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    

    
public:
    Turret();
    void controlTurret();
    void rotateTurret();
    void aimLeft();
    void aimRight();
    //void aimForward();
    //void aimBackwards();
    void setHoodAngle(int position);
    void bangbangControl();
    void aimWithCamera();
    void stopAiming();
    void getCameraData();
    

};