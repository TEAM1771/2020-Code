#ifndef TurnOffShooterAuto_H
#define TurnOffShooterAuto_H

#include "../AutoBase.h"

class TurnOffShooterAuto: public AutoBase
{
public:
	TurnOffShooterAuto() : AutoBase("TurnOffShooterAuto"){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->TurnOff();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
