#pragma once

#include <iostream>

template <class Robot>
class AutoBase {
protected:
    Robot* robot;

public:
    constexpr AutoBase(Robot* robot_)
    : robot { robot } {}
    virtual void init()
    {
        std::cout << "No Auton Mode Selected\n";
    }
    virtual void run() {};
};