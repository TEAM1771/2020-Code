#ifndef OneBallAutoAutoGroup_H
#define OneBallAutoAutoGroup_H

#include "Auto/DriveDistanceAuto.h"
#include "Auto/ToggleShooterPositionAuto.h"
#include "Auto/RotateToAngleAuto.h"
#include "Auto/TurnOnShooterAuto.h"
#include "Auto/TurnOffShooterAuto.h"

class OneBallAutoAutoGroup: public AutoGroup
{
public:
	OneBallAutoAutoGroup() : AutoGroup("OneBallAuto"){
		AddSequential(new TurnOnShooterAuto());
		AddSequential(new ShooterOnTargetAuto());
		AddSequential(new TurnOffShooterAuto());
	}
};

#endif
