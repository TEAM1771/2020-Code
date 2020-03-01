#ifndef ShooterOnTargetAuto_H
#define ShooterOnTargetAuto_H

#include "../AutoBase.h"

class ShooterOnTargetAuto: public AutoBase
{
public:
	ShooterOnTargetAuto(){}
	void Initialize(){}
	void Execute(){}
	bool IsFinished(){
		return shooter->IsOnTarget();
	}
	void End(){}
	void Interrupted(){}
};

#endif
