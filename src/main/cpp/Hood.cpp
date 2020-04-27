#include "Hood.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

Hood::Hood(LimeLight const& limelight)
    : limelight_ { limelight }
{
    hood_.RestoreFactoryDefaults();
    hood_.SetIdleMode(HOOD::IDLE_MODE);

    pidController_.SetP(HOOD::P);
    pidController_.SetI(HOOD::I);
    pidController_.SetD(HOOD::D);

    pidController_.SetFeedbackDevice(encoder_);
    pidController_.SetReference(static_cast<double>(HOOD::POSITION::BOTTOM), rev::ControlType::kPosition);
    pidController_.SetOutputRange(-HOOD::MAX_SPEED, HOOD::MAX_SPEED);
}

bool Hood::goToPosition(HOOD::POSITION position, double tolerance)
{
    if(position != position_)
    {
        pidController_.SetReference(static_cast<double>(position), rev::ControlType::kPosition);
        position_ = position;
    }
    return std::fabs(encoder_.GetPosition() - static_cast<double>(position)) < tolerance;
}

struct table_row
{
    double y_val;
    double hood_val;
};

// bad, but good enough implimentation of std::midpoint from C++20
// remove this if upgraded to C++20
namespace std
{
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> midpoint(A const& a, B const& b)
    {
        return (a + b) / 2;
    }
} // namespace std

// floating point comparison at compile time
constexpr bool is_close_to(auto   value,
                           auto   target,
                           double tol = 0.00001)
{
    return std::fabs(value - target) < tol;
}
static_assert(is_close_to(.1, .100000001));

[[nodiscard]] inline static double getTrackingValue(double yval)
{
    constexpr table_row lookup_table[] {
        { 20.0104, -13.1929 },
        { 10.4538, -17.0433 },
        { 1.97857, -21.3750 },
        { -3.02635, -22.0117 },
        { -5.88120, -21.6297 },
        { -9.15754, -21.3750 }
    };

    auto find_value_in_table = [](auto yval, auto begin, auto end) {
        return std::find_if(std::next(begin), end, [=](auto const& val) {
            return yval >= val.y_val;
        });
    };

    constexpr auto interpolate = [](auto value, table_row const* ref1, table_row const* ref2) {
        return ((ref1->hood_val - ref2->hood_val) / (ref1->y_val - ref2->y_val)) * (value - ref2->y_val) + ref2->hood_val;
    };

    auto const range = find_value_in_table(yval, std::begin(lookup_table), std::end(lookup_table));
    return std::clamp(
        interpolate(yval,
                    std::prev(range),
                    range),
        HOOD::POSITION::SAFE_TO_TURN,
        HOOD::POSITION::TRAVERSE);

    //tests
    static_assert(std::end(lookup_table) - std::begin(lookup_table) >= 2, "lookup table too small");
    // Commented tests are valid C++20
    // static_assert(std::is_sorted(std::begin(lookup_table), std::end(lookup_table), [](auto const &lhs, auto const &rhs) {
    //                   return lhs.y_val > rhs.y_val;
    //               }),
    //               "Lookup table not sorted");

    // static_assert(
    //     find_value_in_table(lookup_table[0].y_val, std::begin(lookup_table), std::end(lookup_table))->y_val ==
    //         lookup_table[1].y_val,
    //     "Invalid Table Search");

    static_assert(is_close_to(std::midpoint(lookup_table[0].hood_val, lookup_table[1].hood_val), interpolate(std::midpoint(lookup_table[0].y_val, lookup_table[1].y_val), &lookup_table[0], &lookup_table[1])),
                  "interpolation error");
}

bool Hood::visionTrack(double tolerance)
{
    if(limelight_.hasTarget())
    {
        double const target = getTrackingValue(limelight_.getY());
        pidController_.SetReference(target, rev::ControlType::kPosition);
        return std::fabs(target - encoder_.GetPosition()) < tolerance;
    }
    else
    {
        goToPosition(HOOD::POSITION::TRAVERSE);
        return false;
    }
}

[[nodiscard]] constexpr double scaleOutput(double inputMin, double inputMax, double outputMin, double outputMax, double input)
{
    return ((input - inputMin) / (inputMax - inputMin)) * ((outputMax - outputMin)) + inputMin;
}

void Hood::manualPositionControl(double position)
{
    pidController_.SetReference(scaleOutput(0,
                                            1,
                                            static_cast<double>(HOOD::POSITION::TRAVERSE),
                                            static_cast<double>(HOOD::POSITION::SAFE_TO_TURN),
                                            std::clamp(position, 0.0, 1.0)),
                                rev::ControlType::kPosition);
}
