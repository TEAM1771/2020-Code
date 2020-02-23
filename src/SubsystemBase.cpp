#include <SubsystemBase.h>

SubsystemBase::SubsystemBase(const std::string &name)
	: Subsystem(name), Command(name){
	this->SetRunWhenDisabled(true);
	this->Start();
}

SubsystemBase::~SubsystemBase() {
}

void SubsystemBase::Execute() {
	Periodic();
}

bool SubsystemBase::IsFinished() {
	return false;
}
