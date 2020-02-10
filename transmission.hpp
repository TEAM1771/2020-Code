/**
 * Revised from https://github.com/TEAM1771/1771-deep-space/blob/master/src/main/include/Transmission.h
 *
 * Authors:
 *    Justin DeSimpliciis - github: jscd
 *    Ryan McHale - github: CrashTestCoder
 *
 * Example Usage:
 *    Transmission<rev::CANSparkMax> transmission{{
 *        {DRIVETRAIN::LTRANS::MTRA, Direction::Reverse}, 
 *        {DRIVETRAIN::LTRANS::MTRB, Direction::Forward}
 *    }};
 *
 *    transmission->Set(0.625);
 */

#pragma once

#include <initializer_list>
#include <vector>
#include <memory>

#include <frc/Encoder.h>
#include <rev/CANSparkMax.h>

enum Direction {
	Forward,
	Reverse
};

template <typename Motor_Controller>
class Transmission {    // CTR
public:

	Transmission(std::initializer_list<std::pair<int, Direction>> motor_info, std::pair<int,int> encPort) : 
			enc( encPort.first, encPort.second ) 
	{
		bool first_run = 0;
		motors.reserve(motor_info.size());
		for(auto const& m_inf : motor_info)
		{
			motors.push_back( std::make_unique<Motor_Controller>( m_inf.first ) );		// add new follower
			auto & motor = *std::prev(std::end(motors));	// create reference to follower

			motor->SetInverted(m_inf.second);

			if(first_run++)	// skips the leader
				motor->Set(ControlMode::Follower, std::begin(motor_info)->first);
		}
	}

	Motor_Controller* operator->() {
		return std::begin(motors)->get();
	}

	int getEncoderPosition() const {
		return enc.Get();
	}

	int getEncoderRate() const {
		return enc.GetRate();
	}

private:
	std::vector<std::unique_ptr<Motor_Controller>> motors;
	frc::Encoder enc;
};

template<>
class Transmission<rev::CANSparkMax> {
public:
	Transmission(std::initializer_list<std::pair<int, Direction>> motor_info)
	{
		bool first_run = 0;
		motors.reserve(motor_info.size());
		for(auto const& m_inf : motor_info)
		{
			motors.emplace_back( std::make_unique<rev::CANSparkMax>( m_inf.first, rev::CANSparkMaxLowLevel::MotorType::kBrushless ) );
			auto & motor = *std::prev(std::end(motors));

			motor->RestoreFactoryDefaults();
			motor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

			if(first_run++) // skips the leader
				motor->Follow(**std::begin(motors), m_inf.second);
		}
		enc = (*std::begin(motors))->GetEncoder();
	}

	auto* operator->() {
		return std::begin(motors)->get();
	}

	void Set(ControlMode cm, double rate) {
		(*std::begin(motors))->Set(rate);
	}

	int getEncoderPosition() {
		return enc.GetPosition();
	}

	int getEncoderRate() {
		return enc.GetVelocity();
	}

private:
	std::vector<std::unique_ptr<rev::CANSparkMax>> motors;
	rev::CANEncoder enc;
};
