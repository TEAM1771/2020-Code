#ifndef StopDriveAuto_H
#define StopDriveAuto_H

#include "../AutoBase.h"

class StopDriveAuto: public AutoBase
{
public:
	StopDriveAuto() : AutoBase("StopDriveAuto"){
		Requires(driveTrain.get());
	}
	void Initialize(){}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
