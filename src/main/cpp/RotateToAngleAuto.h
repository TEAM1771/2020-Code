#ifndef RotateToAngleAuto_H
#define RotateToAngleAuto_H

#include "../AutoBase.h"

class RotateToAngleAuto: public PIDAuto
{
protected:
	double m_angle;
	double m_onTargetTolerance;
	bool m_skip;
	int m_onTarget;
public:
	RotateToAngleAuto(double angle)
			: PIDAuto("RotateToAngle", .04, .025, 0){
		Requires(AutoBase::driveTrain.get());
		m_angle = angle;
		m_onTarget = 0;
		m_onTargetTolerance = 3;
		SmartDashboard::PutNumber("Rotation I Zone", 4);
		SmartDashboard::PutNumber("DriveTrain Rotate D", 0);
		SmartDashboard::PutNumber("DriveTrain Rotate I", .025);
		SmartDashboard::PutNumber("DriveTrain Rotate P", .04);
		SmartDashboard::PutNumber("Rotation Ontarget Time", 5);
	}

	double ReturnPIDInput(){
		return constrain(AutoBase::driveTrain->GetAngle());
	}

	virtual void UsePIDOutput(double output){
		output = std::min(1.0, std::max(-1.0, output));
		AutoBase::driveTrain->TankRaw(output, -output);
	}

	virtual double constrain(double angle) {
		return RoboUtils::constrainDegNeg180To180(angle);
	}

	virtual void Initialize(){
		GetPIDController()->Reset();
		GetPIDController()->Enable();
		m_onTarget = 0;
		m_skip = false;
		m_angle = constrain(m_angle);
		SmartDashboard::PutNumber("Autoed absolute angle", m_angle);
		SetSetpoint(m_angle);
	}

	void Execute(){
		double curError = fabs(GetSetpoint()-GetPosition());
		SmartDashboard::PutNumber("Rotation Error", curError);
		double P = SmartDashboard::GetNumber("DriveTrain Rotate P", 0);
		double D = SmartDashboard::GetNumber("DriveTrain Rotate D", 0);

		std::shared_ptr<PIDController> pid = GetPIDController();
		if (curError < SmartDashboard::GetNumber("Rotation I Zone", 10)) {
			double I = SmartDashboard::GetNumber("DriveTrain Rotate I", 0);
			pid->SetPID(P, I, D);
		}
		else {
			pid->SetPID(P, 0, D);
		}
		if (curError < m_onTargetTolerance) {
			m_onTarget++;
		}
		else {
			m_onTarget = 0;
		}
	}

		return m_onTarget >= SmartDashboard::GetNumber("Rotation Ontarget Time", 5) || m_skip;
	}
	void End(){
		SmartDashboard::PutNumber("Rotate Time", TimeSinceInitialized());
	}
	void Interrupted(){}
};

class RotateToAngleFromCameraAuto : public RotateToAngleAuto {
public:
	RotateToAngleFromCameraAuto() : RotateToAngleAuto(0) {
		m_skip = false;
	}

	void Initialize(){
		m_skip = false;
		m_onTargetTolerance = .5; //.25;
		if(AutoBase::mCameraProcessor->isTargetAvailable()){
			double scale = SmartDashboard::GetNumber("Camera Scale", 1.35275); //30.37 / 14.19; //TODO: Figure out why the camera or gyro angle is wrong.

//			printf("raw relative angle = %f\n", AutoBase::mCameraProcessor->getAngle());
			m_angle = AutoBase::mCameraProcessor->getAngle();
			m_angle *= scale;

//			printf("scaled relative angle = %f\n", m_angle);
			m_angle += AutoBase::driveTrain->GetAngle();

//			printf("current driveTrain angle = %f\n", AutoBase::driveTrain->GetAngle());
//			printf("absolute angle with offset = %f\n", m_angle);
			RotateToAngleAuto::Initialize();
		} else {
			m_skip = true;
		}
	}
};

class Rotate180Auto : public RotateToAngleAuto {
private:
	double m_radiusScale;

public:
	Rotate180Auto(double radiusScale=1) : RotateToAngleAuto(180), m_radiusScale(radiusScale){
	}

	double constrain(double angle) {
		return RoboUtils::constrainDeg0To360(angle);
	}

	void UsePIDOutput(double output){
		output = std::min(1.0, std::max(-1.0, output));
		AutoBase::driveTrain->TankRaw(output, -output * m_radiusScale);
	}
};


#endif
