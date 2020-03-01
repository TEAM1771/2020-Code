#ifndef GeneratedAutoAutoGroup_H
#define GeneratedAutoAutoGroup_H

#include "Auto/DriveDistanceAuto.h"
#include "Auto/ToggleShooterPositionAuto.h"
#include "Auto/RotateToAngleAuto.h"
#include "Auto/TurnOnShooterAuto.h"
#include "Auto/TurnOffShooterAuto.h"

class GeneratedAutoAutoGroup: public AutoGroup
{
public:
	GeneratedAutoAutoGroup(Auto* traverseAuto, int position, int driveBack)
		: AutoGroup("GeneratedAutoAutoGroup"){
		double angleArray[6] = {0, 0, 30, 0, 0, -25};
		if (traverseAuto){
			AddSequential(new AutoBlockOneAutoGroup());
			AddSequential(traverseAuto);

			if (position == 2 || position == 5) {
				AddSequential(new LockOnTargetAuto(CameraProcessor::LEFT_TARGET));
				if (position == 2){
					AddSequential(new DriveDistanceAuto(.6,.6,2000));
				}
			} else {
				AddSequential(new LockOnTargetAuto(CameraProcessor::RIGHT_TARGET));
			}

			AddSequential(new RotateToAngleAuto(angleArray[position]));    //disabling for middle pos
			AddSequential(new AutoBlockTwoAutoGroup());
			AddSequential(new RotateToAngleAuto(0));
			if (position != 2) {
				AddSequential(new DriveDistanceAuto(.5, .5, 2000));
			}
			if (dynamic_cast<TraverseChevalFrieseAutoGroup*>(traverseAuto) != 0) {
				AddSequential(new Rotate180Auto(.5));
			} else {
				AddSequential(new Rotate180Auto());
			}
			if (driveBack==1) {
				AddSequential(new DriveDistanceAuto(.5, .5, 2000));
				AddSequential(traverseAuto);
			}
		}
	}
};

#endif
