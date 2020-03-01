#ifndef RaiseIntakeAuto_H
#define RaiseIntakeAuto_H

#include "../AutoBase.h"

class RaiseIntakeAuto: public AutoBase
{
private:
	bool m_impeded;
public:
	RaiseIntakeAuto() : AutoBase("RaiseIntakeAuto"){
		Requires(intake.get());
		m_impeded = false;
	}
	void Initialize(){
		m_impeded = true;
		if(!kicker->IsExtended()){
			intake->Raise();
			m_impeded = false;
		}
	}
	void Execute(){}
	bool IsFinished(){
		return !intake->IsLowered() || m_impeded;
	}
	void End(){}
	void Interrupted(){}
};

#endif
