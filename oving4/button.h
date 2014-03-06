/* -*- mode: c++ -*-
** button.h
** 
** Made by Kjetil Svarstad
** 
*/

#ifndef   	BUTTON_H_
# define   	BUTTON_H_

#include <systemc.h>

#include "if.h"
const sc_time long_time (100, SC_MS);
const sc_time short_time (30, SC_MS);
//  Our beloved button class (changes are done)
class Button : public sc_module, public Button_if{
public:
  	Button (sc_module_name name, int _id);
	sc_port<bus_push_if> buttonOutPort;
	int id;
	bool light;
	virtual void lights(bool);
	virtual void main();
	sc_signal <bool> PUSH;
	sc_time pushtime;
	sc_time finishtime;
};

#endif 	    /* !BUTTON_H_ */
