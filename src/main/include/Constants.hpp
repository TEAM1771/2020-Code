#pragma once

#include <string>

namespace TRANS
{
    namespace SHIFT_MATH
    {
        constexpr int encoder_cpr = 2048;

        constexpr auto low_ratio = 20.83;
        constexpr auto high_ratio = 9.17;

        constexpr auto wheel_diameter = 7.65;

        constexpr auto low_ratio_multiplier_to_ft = 1.0 / encoder_cpr / low_ratio * wheel_diameter / 2 / 12;
        constexpr auto high_ratio_multiplier_to_ft = 1.0 / encoder_cpr / high_ratio * wheel_diameter / 2 / 12;

    } // SHIFT_MATH

    constexpr int shifter = 0;
    
    constexpr int shift_up_point = 16000;//6 / low_ratio_multiplier_to_ft;
    constexpr int shift_down_point = 6000;//4 / low_ratio_multiplier_to_ft;

    constexpr int rFalcon = 15;    
    constexpr int rNeo = 14;
    constexpr int lFalcon = 17;
    constexpr int lNeo = 11;    
    //std::string song_path = "Pain_it_black.chrp";
} // TRANS
namespace HOPPER
{
    namespace TRANSPORT
    {
        constexpr int PORT = 3;
        constexpr double SPEED = 0.7;
        constexpr double SHOOT_SPEED = 1.0;
    } // TRANSPORT

    namespace INDEXER 
    {
        constexpr int PORT = 10;
        constexpr double SPEED = 1.0;
    }

    // Used to define which motor direction is forward or not, can be negated as needed.
    constexpr double hopperTransportForward = 1.0;
    constexpr double hopperIndexerForward = 1.0;
    constexpr double hopperFeedForward = 1.0;
    //Define motor CAN IDs
    
    constexpr int laserPort = 0; //can be changed later
    constexpr double hopperTimer = 0.251771; //Will need to be changed
}
namespace INTAKE
{
    constexpr int IntakePort = 12;
    constexpr int intakeairport = 1;
}
namespace SHOOTER
{
    namespace WHEEL
    {
        constexpr int PORT_1 = 4;//subject to change
        constexpr int PORT_2 = 5;//subject to change
        constexpr double SHOOTING_RPM = 7500; //Lol no idea
        constexpr double IDLE_RPM = 3000; //lol lets not do this its dumb
        constexpr double P = 0.0001;
        constexpr double I = 0.0001;
        constexpr double D = 0.0001;
        constexpr double FF = 0.1;
    } // SHOOTER

    namespace TURRET
    {
        constexpr int PORT = 6;//subject to change

        constexpr double TRAVERSE_SPEED = 1;
        constexpr double P = 1.0;
        constexpr double I = 0.0;
        constexpr double D = 0.0;

        //Define the 4 quadrants 
        constexpr double FORWARD = 0;
        constexpr double BACKWARDS = 100;
        constexpr double RIGHT = 50;
        constexpr double LEFT = -50;
        
        //Define max travels
        constexpr double MAX_LEFT = -60;
        constexpr double MAX_RIGHT = 60;
    } // TURRET

    
    namespace HOOD
    {
        constexpr int PORT = 7;//subject to change
        
        constexpr double P = 1.0;
        constexpr double I = 0.0;
        constexpr double D = 0.0;

        constexpr int BOTTOM = 0;
        constexpr int TOP = 100;
    } // HOOD

}
namespace BUTTONS
{
    namespace INTAKE
    {
        constexpr int intakedown = 2;
        constexpr int intakein = 3;
        constexpr int intakeout = 5;
    }
    namespace TURRET
    {
        constexpr int AIM_LEFT = 6;
        constexpr int AIM_RIGHT = 7;
        constexpr int AIM_LEFT_MANUAL = 9;
        constexpr int AIM_RIGHT_MANUAL = 8;
        constexpr int AIM_CAMERA = 10;
    }
    namespace HOPPER
    {
        constexpr int SHOOT = 1;
    }

}