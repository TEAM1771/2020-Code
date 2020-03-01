#ifndef RetractIntakeAuto_H
#define RetractIntakeAuto_H

#include "../AutoBase.h"

class RetractIntakeAuto: public AutoBase
{
public:
	RetractIntakeAuto() : AutoBase("RetractIntakeAuto"){
		Requires(intake.get());
	}
	void Initialize(){
		if (!kicker->IsExtended()) {
			intake->Retract();
			intake->TurnOff();
		}
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
