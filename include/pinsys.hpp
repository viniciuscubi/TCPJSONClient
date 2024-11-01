#ifndef PINSYS_HPP
#define PINSYS_HPP

#include <pigpio.h>
#include <iostream>

class PinSys{
	
	private:
		int pin;
	
	public:
		PinSys(int p);
		~PinSys();
		void updatePin(bool var);
	
};

#endif