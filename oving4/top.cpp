#include <systemc.h>

#include "if.h"
#include "button.h"
#include "control.h"
#include "adapter.h"

#include "simple_bus.h"
#include "simple_bus_fast_mem.h"
#include "simple_bus_arbiter.h"

class top : public sc_module {
public:
	Control *ctrlunit;
	Button *button[10];
	Adapter *adapter[10];

	simple_bus *bus;
	simple_bus_fast_mem *FastMem;
	simple_bus_arbiter *arbit;
	sc_clock C1;

	char namebufbut[40];
	char namebufadapt[40];

	void testbed();
	void finger(int);

	top (sc_module_name name) : sc_module (name){
		cout << "Instantiating system" << endl;
		FastMem = new simple_bus_fast_mem("FastMem", 0x002C, 0x042B);
		cout << "FastMem OK" << endl;
		ctrlunit = new Control("Controlunit", 0x0000, 0x0003);
		arbit = new simple_bus_arbiter("Arbiter");
		
		cout << "Creating ports" << endl;
		bus->clock(C1);
		cout << "Clock ok" << endl;
		bus->arbiter_port(*arbit);
		cout << "Arbiter ok" << endl;
	  	bus->slave_port(*FastMem);
	  	cout << "Fastmem ok" << endl;
	  	ctrlunit->controlOutPort(*bus);
	  	bus->slave_port(*ctrlunit);
	  	

	  	cout << "Making buttons" << endl;
	  		for ( int i = 0; i < 10; i++){
				sprintf (namebufbut, "Button%d\0", i);
				sprintf (namebufadapt, "Adapter%d\0", i); 
				button[i] = new Button(namebufbut,i);
				adapter[i] = new Adapter(namebufadapt,i, 0x0004+4*i);
				button[i]->buttonToAdapterPort(*adapter[i]);		
				adapter[i]->adapterToButtonPort(*button[i]);
				bus->slave_port(*adapter[i]);
				adapter[i]->adapterToBusPort(*bus);
			}
		SC_HAS_PROCESS(top);
		SC_THREAD(testbed);
	}	
};

void top::testbed(){
	while(1) {
	cout << "Testbed started" << endl;
	wait(500*ms);
	finger(0); //See function finger(int), which simulates a button being pushed
	wait(500*ms);
	finger(3);
	wait(500*ms);
	finger(4);
	wait(500*ms);
	finger(1);
	wait(500*ms);
	finger(9);
	wait(500*ms);
	finger(6);
	wait(500*ms);
	finger(8);
	wait(500*ms);
	finger(7);
	wait(500*ms);
	finger(2);
	wait(500*ms);
	finger(5);
	wait(500*ms);

	sc_stop();
}

}

void top::finger(int btn){ //simulating fingerpush
	button[btn]->PUSH = true;
	wait(100*ms); // Tr = 100 ms
	button[btn]->PUSH = false;
}

int sc_main (int argc , char *argv[])  {
	top top1("Top1");
  	
  	sc_start ();
	return 0;
};