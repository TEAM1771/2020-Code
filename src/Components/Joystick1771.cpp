#include "Joystick1771.h"
#include <math.h>

Joystick1771::Joystick1771(int port) : Joystick(port) {
	s = 0.375;
	m = 1.340508;
	t = 0.381021;
	b = -0.340508;
}

Joystick1771::~Joystick1771() {
	// TODO Auto-generated destructor stub
}

float Joystick1771::GetRawAxis(int axis, bool boost) {
	float x = Joystick::GetRawAxis(axis);
	float scale = boost ? 1.0f:0.5f;

    if (x < -t){
        return scale * (m * x - b);
    }
    if (x > -t && x < t){
        return scale * (1 / (pow(s,2.0)) * pow(x,3.0));
    }
    else{
        return scale * (m * x + b);
    }
	
}
