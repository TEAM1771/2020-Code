#ifndef JOYSTICK2481_H_
#define JOYSTICK2481_H_

#include "Joystick.h"

class Joystick2481 : public Joystick {
private:
	static char inputShape[255];
	double s;
	double m;
	double b;
	double t;
public:
	Joystick1771(int port);
	virtual ~Joystick1771();
	virtual float GetRawAxis(int axis, bool boost = false);
};

#endif /* JOYSTICK1771_H_ */
