#ifndef LowerIntakeAuto_H
#define LowerIntakeAuto_H

#include "../AutoBase.h"

class LowerIntakeAuto: public AutoBase
{
private:
	bool m_impeded;
public:
	LowerIntakeAuto() : AutoBase("LowerIntakeAuto"){
		Requires(intake.get());
		m_impeded = false;
	}
	void Initialize(){
		m_impeded = true;
		if(!kicker->IsExtended()){
			intake->Lower();
			m_impeded = false;
		}
	}
	void Execute(){}
	bool IsFinished(){
		return intake->IsLowered() || m_impeded;
	}
	void End(){}
	void Interrupted(){}
};

#endif
