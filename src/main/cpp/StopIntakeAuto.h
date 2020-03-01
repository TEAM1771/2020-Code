#ifndef StopIntakeAuto_H
#define StopIntakeAuto_H

#include "../AutoBase.h"

class StopIntakeAuto: public AutoBase
{
public:
	StopIntakeAuto() : AutoBase("StopIntakeAuto"){
		Requires(intake.get());
	}
	void Initialize(){
		intake->SetSpeed(0);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
