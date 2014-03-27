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
#include "simple_bus_blocking_if.h"
#include "simple_bus.h"
#include "if.h"

//  Our beloved control class (changes made)
class Control : public sc_module, Control_if , public simple_bus_slave_if{
public:
  	Control (sc_module_name, int , int );
	//Port
	sc_port<simple_bus_blocking_if> controlOutPort;
	
	//Functions
	virtual void pushed(int);
	virtual void clearButtonLights();
	virtual void mainc();
	virtual void lights(int, bool);
	unsigned int start_address() const;
	unsigned int end_address() const;
	bool direct_read(int *, unsigned int );
	bool direct_write(int *, unsigned int );
	simple_bus_status read(int *, unsigned int ) ;
	simple_bus_status write(int *, unsigned int );
private:
	int start_addr;
  	int end_addr;
  	int rawData;

private:
	static int nextnumber;
  	static const int X[9];
  	
};


#endif 	    /* !CONTROL_H_ */