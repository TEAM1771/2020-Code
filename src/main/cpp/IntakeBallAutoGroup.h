#ifndef IntakeBallAutoGroup_H
#define IntakeBallAutoGroup_H

#include "Auto/DriveDistanceAuto.h"
#include "Auto/ToggleShooterPositionAuto.h"
#include "Auto/RotateToAngleAuto.h"
#include "Auto/TurnOnShooterAuto.h"
#include "Auto/TurnOffShooterAuto.h"

class IntakeBallAutoGroup: public AutoGroup
{
public:
	IntakeBallAutoGroup() : AutoGroup("IntakeBallAutoGroup"){
		//AddSequential(new RetractKickerAuto());
		AddSequential(new LowerIntakeAuto());
		AddSequential(new TurnIntakeOnFwdAuto());
	}
};

#endif
