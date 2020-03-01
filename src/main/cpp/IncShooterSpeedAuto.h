#ifndef IncShooterSpeedAuto_H
#define IncShooterSpeedAuto_H

#include "../AutoBase.h"

class IncShooterSpeedAuto: public AutoBase
{
public:
	IncShooterSpeedAuto() : AutoBase("IncShooterSpeedAuto"){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		shooter->incShooterSpeed();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
