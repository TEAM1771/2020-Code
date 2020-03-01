#ifndef LockOnTargetAuto_H
#define LockOnTargetAuto_H

#include "../AutoBase.h"

class LockOnTargetAuto: public AutoBase
{
private:
	CameraProcessor::target_type_t m_target;

public:
	LockOnTargetAuto(CameraProcessor::target_type_t target)
		: AutoBase("LockOnTargetAuto"), m_target(target) {
	}
	void Initialize(){
		AutoBase::mCameraProcessor->lockOnTarget(m_target);
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
