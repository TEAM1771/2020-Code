#ifndef ToggleIntakeAuto_H
#define ToggleIntakeAuto_H

#include "../AutoBase.h"

class ToggleIntakeAuto: public AutoBase
{

public:
	ToggleIntakeAuto() : AutoBase("ToggleIntakeAuto"){
		Requires(intake.get());
	}
	void Initialize(){
		if(intake->IsLowered()){
			intake->Raise();
		}else{
			intake->Lower();
		}
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){
		End();
	}
};

#endif
