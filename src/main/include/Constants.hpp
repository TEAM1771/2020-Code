#pragma once

#include <string>

namespace TRANS
{
    constexpr int shifter = 0;

    constexpr int encoder_cpr = 2048;

    constexpr auto low_ratio = 20.83;
    constexpr auto high_ratio = 9.17;

    constexpr auto wheel_diameter = 7.65;

    constexpr auto low_ratio_multiplier_to_ft = 1.0 / encoder_cpr / low_ratio * wheel_diameter / 2 / 12;
    constexpr auto high_ratio_multiplier_to_ft = 1.0 / encoder_cpr / high_ratio * wheel_diameter / 2 / 12;

    constexpr int shift_up_point = 6 / low_ratio_multiplier_to_ft;
    constexpr int shift_down_point = 4 / low_ratio_multiplier_to_ft;

    constexpr int rFalcon = 15;    
    constexpr int rNeo = 14;
    constexpr int lFalcon = 17;
    constexpr int lNeo = 11;    
    //std::string song_path = "paint";
<<<<<<< Updated upstream
} // TRANS
=======
} // TRANS
namespace HOPP
{
    //Hopper Constants

    // Used to define which motor direction is forward or not, can be negated as needed.
    constexpr double hopperTransportForward = 0.7;
    constexpr double hopperIndexerForward = 1.0;
    constexpr double hopperFeedForward = 1.0;
    //Define motor CAN IDs
    constexpr int hopperTransportNeo = 3;
    constexpr int hopperIndexerNeo = 10;
    
    constexpr int laserPort = 4; //can be changed later
    constexpr double hopperTimer = 0.21771; //Will need to be changed
}
namespace INTAKE
{
    constexpr int IntakePort = 12;
    constexpr int intakeairport = 1;
    namespace BUTTONS
    { 
        constexpr int intakedown = 2;
        constexpr int intakein = 3;
        constexpr int intakeout = 5;
    }
}
>>>>>>> Stashed changes
