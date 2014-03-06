#include <systemc.h>

#include "if.h"
#include "button.h"
#include "control.h"


class top : public sc_module {
public:
	top (sc_module_name name) : sc_module (name){};

};

int sc_main (int argc , char *argv[])  {
  	// instantiate top
	top top1("Top1");
  	// tracing of signals ...
  	// sc_start
  	sc_start ();
	return 0;
};