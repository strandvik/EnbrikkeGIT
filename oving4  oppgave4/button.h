/* -*- mode: c++ -*-
** button.h*/

#ifndef   	BUTTON_H_
# define   	BUTTON_H_

#include <systemc.h>
#include "if.h"

class Button : public sc_module, public Button_if{
public:
  	Button (sc_module_name name, int _id);
	sc_port<Adapter_if> buttonToAdapterPort;

	int id;
	bool light;

	virtual void lights(bool);
	virtual void main();


	sc_signal <bool> PUSH;
	sc_time pushtime;
	sc_time finishtime;
};

#endif 	    /* !BUTTON_H_ */
