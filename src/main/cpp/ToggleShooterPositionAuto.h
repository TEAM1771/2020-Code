#ifndef ToggleShooterPositionAuto_H
#define ToggleShooterPositionAuto_H

#include "../AutoBase.h"

class ToggleShooterPositionAuto: public AutoBase
{
public:
	ToggleShooterPositionAuto() : AutoBase("ToggleShooterPositionAuto"){
		Requires(shooter.get());
	}
	void Initialize(){
		if (shooter->GetPosition() == false) {
			shooter->SetHighPosition();
		}
		else {
			shooter->SetLowPosition();
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
