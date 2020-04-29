#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

template <class Robot>
class AutoBase
{
protected:
    Robot* robot;

public:
    constexpr AutoBase(Robot* robot_)
        : robot { robot }
    {}
    virtual void init()
    {
        std::cout << "No Auton Mode Selected\n";
    }
    virtual void run() {};

    bool is_auto() const
    {
        return robot->IsAutonomous() && robot->IsEnabled();
    }
};

template <typename Time_t, typename FUNC, typename... Params>
[[nodiscard]] static std::thread&& start_after(Time_t time, std::function<FUNC> func, Params... params)
{
    return std::thread { [&] {
        std::this_thread::sleep_for(time);
        func(params...);
    } };
}