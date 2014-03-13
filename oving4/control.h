/* -*- mode: c++ -*-
** control.h
*/

#ifndef   	CONTROL_H_
# define   	CONTROL_H_

#ifndef CONTROL_ADDRESS
#define CONTROL_ADDRESS 0x0000
#endif

#ifndef BUTTON_ADDR
#define BUTTON_ADDR 0x0004
#endif

#include <systemc.h>
#include "simple_bus_direct_if.h"
#include "if.h"

//  Our beloved control class (changes made)
class Control : public sc_module, public simple_bus_direct_if, public simple_bus_blocking_if{
public:
  	Control (sc_module_name);
	sc_port<simple_bus_direct_if> controlOutPort;
	virtual void pushed(int);
	virtual void clearButtonLights();
	virtual void main();
	virtual void lights(int, bool);
private:
	static int nextnumber;
  	static const int X[9];
	sc_mutex control_access;
};


#endif 	    /* !CONTROL_H_ */