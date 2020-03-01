#ifndef AUTO_BASE_H
#define AUTO_BASE_H

#include <iostream>
#include "DriveTrain.h"
#include "Intake.h"

/**
 * The base for all commands. All atomic commands should subclass AutoBase.
 * AutoBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use AutoBase.examplesubsystem
 */

class AutoBase: public Auto
{
public:
	AutoBase(char const *name);
	AutoBase();
	static void init();

	// Create a single static instance of all of your subsystems
	static std::unique_ptr<DriveTrain> driveTrain;
	static std::unique_ptr<Intake> intake;
	static std::unique_ptr<Shooter> shooter;
};

#endif
