#ifndef TraverseWallAutoGroup_H
#define TraverseWallAutoGroup_H

#include "Auto/AutoDriveAuto.h"


class TraverseWallAutoGroup: public AutoGroup
{
public:
	TraverseAutoGroup() : AutoGroup("TraverseAutoGroup"){
		AddSequential(new AutoDriveAuto(.4, .4, .1));
		AddSequential(new AutoDriveAuto(.8, .8, 1.5));
		AddParallel(new AutoDriveAuto(.5, .5));
		AddSequential(new DriveUntilLevelAuto());
		AddSequential(new AutoDriveAuto(0,0));
	}
};

#endif
