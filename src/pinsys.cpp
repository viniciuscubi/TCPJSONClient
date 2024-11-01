#include "../include/pinsys.hpp"


//Initialize a GPIO pin for the test
PinSys::PinSys(int p){
	pin = p;
	
	//start GPIO library
	if (gpioInitialise() < 0) {
        std::cerr << "Error in initialize pigpio library." << std::endl;
    }
	
	std::cout << "Initialized" << std::endl;
	
	//Configure the GPIO pin as output
	gpioSetMode(pin, PI_OUTPUT);
}

//Terminate the GPIO library
PinSys::~PinSys(){
	//Free the pins alocated int the GPIO port
	std::cout << "ended" << std::endl;
    gpioTerminate();
	
}

//Change pin value
void PinSys::updatePin(bool var){
	

	gpioWrite(pin, var);
	
	
}