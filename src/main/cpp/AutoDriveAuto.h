#ifndef AutoDriveAuto_H
#define AutoDriveAuto_H

#include "AutoBase.h"

class AutoDriveAuto: public AutoBase
{
private:
	double m_right;
	double m_left;
	bool m_timeoutSet;
public:
	AutoDriveAuto(double right, double left, double timeout = 0)
		: AutoBase("AutoDriveAuto"), m_right(right), m_left(left){
		Requires(driveTrain.get());
		if (timeout > 0) {
			SetTimeout(timeout);
			m_timeoutSet = true;
		}
		else {
			m_timeoutSet = false;
		}
	}
	void Initialize(){}
	void Execute(){
		driveTrain->Tank(-m_right, -m_left);
	}
	bool IsFinished(){
		return IsTimedOut() || !m_timeoutSet;
	}
	void End(){
		if (m_timeoutSet) {
			driveTrain->StopMotors();
		}
	}
	void Interrupted(){
		End();
	}
};

#endif
