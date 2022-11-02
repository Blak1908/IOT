#ifndef __DC_H__
#define __DC_H__

#include "Arduino.h"
class DC{
 public:
	unsigned char dir;
	unsigned char pwm;
	DC(unsigned char d, unsigned char p);
	void init();
	void forward(unsigned char s);
	void backward(unsigned char s);
};

#endif //__DC_H__
