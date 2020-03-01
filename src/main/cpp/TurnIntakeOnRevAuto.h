#ifndef TurnIntakeOnRevAuto_H
#define TurnIntakeOnRevAuto_H

#include "../AutoBase.h"

class TurnIntakeOnRevAuto: public AutoBase
{
public:
	TurnIntakeOnRevAuto() : AutoBase("TurnIntakeOnRevAuto"){
		Requires(intake.get());
	}
	void Initialize(){
		intake->SetSpeed(INTAKE_REV_SPD);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
