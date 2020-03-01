#ifndef DecrementShooterSpeedAuto_H
#define DecrementShooterSpeedAuto_H

#include "../AutoBase.h"

class DecrementShooterSpeedAuto: public AutoBase
{
public:
	DecrementShooterSpeedAuto() : AutoBase("DecrementShooterSpeedAuto"){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		shooter->decShooterSpeed();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
