#include "AutoBase.h"

// Initialize a single static instance of all of your subsystems to NULL
std::unique_ptr<DriveTrain> AutoBase::driveTrain;
std::unique_ptr<Intake> AutoBase::intake;
std::unique_ptr<Shooter> AutoBase::shooter;

AutoBase::AutoBase(char const *name) :
		Auto(name)
{
}

AutoBase::AutoBase() :
		Auto()
{

}

void AutoBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.

	driveTrain.reset(new DriveTrain());
	intake.reset(new Intake());
	shooter.reset(new Shooter());
}
