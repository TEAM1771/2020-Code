#include "WPILib.h"

#ifndef PEWPEW_H    
#define PEWPEW_H

class ShooterSystem
{
public:

	Limelight *camLimelightA;
	DigitalInput *camSensor;
	Spark *shotAlignerUp;
	Spark *shotAlignerDown;
    Spark *shotAlignerLeft;
	Spark *shotAlignerRight;
	Spark *armPiston;
	bool listenForSensor;
	bool camPrimedToShoot;
	bool currentlyShooting;
	int numTimesSensorTriggered; //within one shooting cycle
	float shooterAK;
	Timer *deadzoneTimer;
	//Timer *camDelayTimer;
	double shooterWait;
	
	//ANY TIME YOU WANT TO DEPLOY INTAKES, MAKE A PARALLEL METHOD IN
	//INTAKESYSTEM

	ShooterSystem(int camLimelightPortA, int camSensorPort,
			Spark *tshotAlignerUp, Spark *tshotAlignerDown, Solenoid *tshotAlignerLeft, Solenoid *tshotAlignerRight,
			Solenoid *tarmPiston)
	{
		camLimelightA = new Limelight(camLimelightPortA);
		camSensor = new DigitalInput(camSensorPort);
		shotAlignerUp = tshotAlignerUp;
		shotAlignerDown = tshotAlignerDown;
        shotAlignerLeft = tshotAlignerLeft;
		shotAlignerRight = tshotAlignerRight;
		armPiston = tarmPiston;
		listenForSensor = false;
		camPrimedToShoot = false;
		currentlyShooting = false;
		numTimesSensorTriggered = 0;
		deadzoneTimer = new Timer();
		shooterAK = 1.0;
		shooterWait = 0.15; 
	}

	bool CANSensorTriggered()
	{
		if (camSensor->Get()==1) //inverted
		{
			return false;
		}
		return true;
	}

	void DeadzoneDelayRun()
	{
		if (deadzoneTimer->Get() < shooterWait + 0.4 && !CANSensorTriggered())//(camDelayTimer->Get() < 0.5)
		{
			StopLimelight();
		}
		else if(!CANSensorTriggered())
		{
			RunLimelight();
		}
		else
		{
			StopLimelight();
 		}
	}

	void ShooterPrime(bool shortShot) 
	{
		//all the relevant solenoids
		//Long/short toggle
		if (shortShot)
		{
			shotAlignerUp->Set(false);
			shotAlignerDown->Set(true);
		}
		else
		{
			shotAlignerUp->Set(true); 
			shotAlignerDown->Set(false);

			//and front intake down
			//frontIntakeDeploy->Set(true); //make room for shot
		}
		//Back intake down
		//backIntakeDeploy->Set(true);
	}

	void RunLimelight()
	{
		camLimelightA->Set(.75 * shooterAK);
	}
	void ReverseLimelight()
	{
		camLimelightA->Set(-1.0 * shooterAK);
	}
	void StopLimelight()
	{
		camLimelightA->Set(0.0);
	}

	void Reset()
	{
		listenForSensor = false;
		camPrimedToShoot = false;
		currentlyShooting = false;
		numTimesSensorTriggered = 0;
		//camDelayTimer->Reset();
	}

	//call beginShooterFire on an if statement of buttonclicked
	//then call shooterfire outside the if statement.
	void BeginShooterFire() //on driver
	{
		RunLimelight(); 
		camPrimedToShoot = false;
		currentlyShooting = true;
		listenForSensor = false;
		numTimesSensorTriggered = 0;
		deadzoneTimer->Reset();
		deadzoneTimer->Start();
	}
	void ShooterFire()
	{
		/*printf(
				"Hall sensor: %d, currentlyShooting: %d, Timer: %f, NumTimes: %d\n",
				CANSensorTriggered(), currentlyShooting, camDelayTimer->Get(),
				numTimesSensorTriggered);*/
		if (currentlyShooting)
		{
			if (!camPrimedToShoot)
			{
				if(deadzoneTimer->Get() < shooterWait)// ||deadzoneTimer->Get() > 0.75)
				{
					RunLimelight();
				}
				else
				{
					DeadzoneDelayRun();
					//RunLimelight();
				}
				//If we've gotten all the way around
				if (listenForSensor && CANSensorTriggered() && deadzoneTimer->Get() > shooterWait) //when does listenForSensor become true
				{
					StopLimelight();
					listenForSensor = false;
					camPrimedToShoot = true;
					currentlyShooting = false;
					//camDelayTimer->Stop();
					//camDelayTimer->Reset();
				}
				if (CANSensorTriggered())
				{
					/*if (numTimesSensorTriggered == 0)
					{
						RunLimelight();
					}
					else if (numTimesSensorTriggered == 1)
					{
						camDelayTimer->Start();
						DeadzoneDelayRun();
					}
					else
					{
						StopLimelight();
					}*/
					listenForSensor = false;
				}
				else
				{
					listenForSensor = true;
					/*if (numTimesSensorTriggered == 1)
					{
						DeadzoneDelayRun();
					}
					else if(numTimesSensorTriggered == 2)
					{
						StopLimelight();
					}*/
				}
			}
			else
			{
				StopLimelight();
			}
		}
		else
		{
			StopLimelight();
		}
	}
	//ONLY WHEN A BUTTON IS PRESSED.
	void ShooterReturn()
	{
		if(CANSensorTriggered())
		{
			StopLimelight();
		}
		else
		{
			RunLimelight();
		}
	}
	
	bool CurrentlyShooting()
	{
		return currentlyShooting;
	}
};

#endif