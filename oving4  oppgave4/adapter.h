/* -*- mode: c++ -*-
** adapter.h*/

#ifndef   	ADAPTER_H
# define   	ADAPTER_H

#include <systemc.h>
#include "if.h"
#include "button.h"
#include "simple_bus_blocking_if.h"
#include "simple_bus.h"



class Adapter : public sc_module, public Adapter_if, public simple_bus_slave_if{
public:
	//Constructor
  	Adapter (sc_module_name name, int, int);
	//Ports
	sc_port<Button_if> adapterToButtonPort;
	sc_port<simple_bus_blocking_if> adapterToBusPort;
	//Functions
	void pushed(int);
	void send(int, int);
	unsigned int start_address() const;
	unsigned int end_address() const;
	bool direct_read(int *, unsigned int );
	bool direct_write(int *, unsigned int );
	simple_bus_status read(int *, unsigned int );
	simple_bus_status write(int *, unsigned int );

	//Variables
private:
	int id;
	int start_addr;
	int nextFreeAddress;
  	//int end_addr;
		
};

#endif 	    /* !ADAPTER_H */
