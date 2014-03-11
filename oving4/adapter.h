/* -*- mode: c++ -*-
** adapter.h*/

#ifndef   	ADAPTER_H
# define   	ADAPTER_H

#include <systemc.h>
#include "if.h"
#include "button.h"
#include "simple_bus_slave_if.h"
#include "simple_bus_blocking_if.h"


const sc_time long_time (100, SC_MS);
const sc_time short_time (30, SC_MS);

//  Our beloved button class (changes are done)
class Adapter : public sc_module, public simple_bus_slave_if, public bus_push_if{
public:
  	Adapter (sc_module_name name, int _id);
	sc_port<button_if> adapterToButtonPort;
	sc_port<simple_bus_blocking_if> adapterToBusPort;
	void pushed(int);
	int id;
	int address;
	void send(int, int);	
};

#endif 	    /* !ADAPTER_H */
