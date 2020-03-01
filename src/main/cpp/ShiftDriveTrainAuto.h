#ifndef ShiftDriveTrainAuto_H
#define ShiftDriveTrainAuto_H

#include "../AutoBase.h"

class ShiftDriveTrainAuto: public AutoBase
{
private:
	bool m_shiftState;
public:
	ShiftDriveTrainAuto(bool state) : AutoBase("ShiftDriveTrainAuto"){
		Requires(driveTrain.get());
		m_shiftState = state;
	}
	void Initialize(){
		driveTrain->SetShifter(m_shiftState);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
