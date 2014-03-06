/* -*- mode: c++ -*-
** control.h
** 
** Made by Kjetil Svarstad
** 
*/

#ifndef   	CONTROL_H_
# define   	CONTROL_H_

#include <systemc.h>

#include "if.h"
const sc_time ctrl_delay (20, SC_MS);
const sc_time ctrl_mutex_delay (16, SC_MS);
//  Our beloved control class (changes made)
class Control : public sc_module, public Control_if
{
public:
  	Control (sc_module_name);
	sc_port<bus_light_if> controlOutPort;
	virtual void pushed(int);
	virtual void clearButtonLights();

private:
	static int nextnumber;
  	static const int X[9];
	sc_mutex control_access;

};


#endif 	    /* !CONTROL_H_ */
