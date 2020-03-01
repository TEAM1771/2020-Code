
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
    rev::CANEncoder hood_encoder = hood.GetEncoder();

    double turnyturnyEncoderTicks;
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
    void setHoodAngle(double position);
    void debugSetHoodAngle(double position);
    void bangbangControl();
    void aimWithCamera();
    void getCameraData();
    void batterShotPosition();
    void maintainRPM();
    void rpmWithStick(float value);
    void stopShooter();
    void aimWithCameraLimelight();

    void stopAiming();
    void aimLeftPID();
    void aimRightPID();
    void aimZero();
    void zeroHood();
    void midHood();
    void batterHood();
    void traverseHood();

    void limelight_led(bool);

    void giveStatus();
    double scaleOutput(double inputMin, double inputMax, double outputMin, double outputMax, double input);
    double getHoodAngle(double height);
    bool valueInRange(double value, double min, double max);
    double getTurnyTurnyValue();
    double getHoodValue();
    double getCameraY(); // for debug, bad default
};