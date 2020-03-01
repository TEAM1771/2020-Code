#ifndef TurnIntakeOnFwdAuto_H
#define TurnIntakeOnFwdAuto_H

#include "../AutoBase.h"

class TurnIntakeOnFwdAuto: public AutoBase
{
public:
	TurnIntakeOnFwdAuto() : AutoBase("TurnIntakeOnFwdAuto"){
		Requires(intake.get());
	}
	void Initialize(){
		intake->SetSpeed(intake->GetIntakeSpeed());
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
