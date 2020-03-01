#ifndef GeneratedAutoBatterShotsAutoGroup_H
#define GeneratedAutoBatterShotsAutoGroup_H

#include "Auto/DriveDistanceAuto.h"
#include "Auto/ToggleShooterPositionAuto.h"
#include "Auto/RotateToAngleAuto.h"
#include "Auto/TurnOnShooterAuto.h"
#include "Auto/TurnOffShooterAuto.h"

class GeneratedAutoBatterShotsAutoGroup: public AutoGroup
{
public:
	GeneratedAutoBatterShotsAutoGroup(Auto* traverseAuto, int position) : AutoGroup("GeneratedAutoBatterShotsAutoGroup") {
		double angleArray[4] = {55.9, 28, 333.5, 309.9};
		double distanceArray[4] = {65809, 14252, 11085, 22697};
		if (traverseAuto){
			AddSequential(new ToggleShooterPositionAuto());
			AddSequential(new AutoBlockOneAutoGroup());
			AddSequential(traverseAuto);
			AddSequential(new RotateToAngleAuto(angleArray[position - 2]));
			AddSequential(new WaitAuto(.25));
			AddSequential(new DriveDistanceAuto(.7,.7,distanceArray[position - 2]));
			AddSequential(new WaitAuto(.25));
			AddSequential(new RotateToAngleAuto(0));
			AddParallel(new AutoDriveAuto(.5,.5));
			AddSequential(new DriveUntilBatterAuto());
			AddSequential(new FireBallAutoGroup());
			AddSequential(new TurnOffShooterAuto());
			AddParallel(new AutoDriveAuto(-.5,-.5,.5));
			AddSequential(new ToggleShooterPositionAuto());
		}

	}
};

#endif
