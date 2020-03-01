#ifndef BringIntakeUpAutoGroup_H
#define BringIntakeUpAutoGroup_H

#include "RaiseIntakeAuto.h"
#include "StopIntakeAuto.h"

class BringIntakeUpAutoGroup: public AutoGroup
{
public:
	BringIntakeUpAutoGroup() : AutoGroup("BringIntakeUpAutoGroup"){
		AddParallel(new RaiseIntakeAuto());
		AddSequential(new WaitAuto(1.5));
		AddSequential(new StopIntakeAuto());
	}
};

#endif
