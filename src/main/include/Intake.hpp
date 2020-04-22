#include "Constants.hpp"
#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>

class Intake
{
    frc::Solenoid intakeair { INTAKE::PCM_PORT };
    bool intakeDeployed = false;
public:
    rev::CANSparkMax wheels {INTAKE::PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    Intake();
    void deploy(bool val);
    [[nodiscard]] bool isIntakeDown() const;

};