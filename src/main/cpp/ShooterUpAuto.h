#ifndef ShooterUpAuto_H
#define ShooterUpAuto_H

#include "../AutoBase.h"

class ShooterUpAuto: public AutoBase
{
public:
	ShooterUpAuto() : AutoBase("ShooterUpAuto"){}
	void Initialize(){
		shooter->SetHighPosition();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
