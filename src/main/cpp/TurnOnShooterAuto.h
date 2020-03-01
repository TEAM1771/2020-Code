#ifndef TurnOnShooterAuto_H
#define TurnOnShooterAuto_H

#include "../AutoBase.h"

class TurnOnShooterAuto: public AutoBase
{
public:
	TurnOnShooterAuto() : AutoBase("TurnOnShooterAuto"){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->SetShooterSpeed();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
