#ifndef CancelIfShooterNotOnTargetAuto_H
#define CancelIfShooterNotOnTargetAuto_H

#include "../AutoBase.h"

class CancelIfShooterNotOnTargetAuto: public AutoBase
{
public:
	CancelIfShooterNotOnTargetAuto(){}
	void Initialize(){
		if(!shooter->IsOnTarget() && Auto::GetGroup()){
			Auto::GetGroup()->Cancel();
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
