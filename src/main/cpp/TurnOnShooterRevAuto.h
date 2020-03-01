#ifndef TurnOnShooterRevAuto_H
#define TurnOnShooterRevAuto_H

#include "../AutoBase.h"

class TurnOnShooterRevAuto: public AutoBase
{
public:
	TurnOnShooterRevAuto() : AutoBase("TurnOnShooterRevAuto"){
		Requires(shooter.get());
	}
	void Initialize(){
		shooter->SetShooterSpeed(false);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		shooter->TurnOff();
	}
	void Interrupted(){
		End();
	}
};

#endif
