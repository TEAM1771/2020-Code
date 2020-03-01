#ifndef ExtendIntakeAuto_H
#define ExtendIntakeAuto_H

#include "../AutoBase.h"

class ExtendIntakeAuto: public AutoBase
{
public:
	ExtendIntakeAuto() : AutoBase("ExtendIntakeAuto"){
		Requires(intake.get());
	}
	void Initialize(){
		if (!kicker->IsExtended()) {
			intake->TurnOnFwd();
			intake->Extend();
		}
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){
	}
	void Interrupted(){}
};

#endif
