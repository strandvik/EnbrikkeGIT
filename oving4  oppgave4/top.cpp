#include <systemc.h>

#include "if.h"
#include "button.h"
#include "control.h"
#include "adapter.h"

#include "simple_bus.h"
#include "simple_bus_fast_mem.h"
#include "simple_bus_arbiter.h"


const sc_time period (1, SC_US);
class top : public sc_module {
public:
	Control *ctrlunit;
	Button *button[10];
	Adapter *adapter[10];

	simple_bus *bus;
	simple_bus_fast_mem *FastMem;
	simple_bus_arbiter *arbit;

	sc_clock C1; //("clk", sc_time(1,SC_ms));
	//sc_clock C1("C1", period);
	char namebufbut[40];
	char namebufadapt[40];

	void testbed();
	void finger(int);

	top (sc_module_name name) : sc_module (name) , C1("C1", period){
		cout << "Instantiating system" << endl;
		FastMem = new simple_bus_fast_mem("FastMem", 0x002C, 0x102B);
		ctrlunit = new Control("Controlunit", 0x0000, 0x0003);
		arbit = new simple_bus_arbiter("Arbiter");
		bus = new simple_bus("bus");
		
		bus->clock(C1);
		bus->arbiter_port(*arbit);
	  	bus->slave_port(*FastMem);
	  	ctrlunit->controlOutPort(*bus);
	  	bus->slave_port(*ctrlunit);	 
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
	wait(1*ns);
	cout << "Testbed started" << endl;
	//wait(100*ms);
	button[0]->PUSH = true;
	wait(ms);
	button[0]->PUSH = false;
	wait(500*ms);
	button[3]->PUSH = true;
	wait(ms);
	button[3]->PUSH = false;
	wait(500*ms);
	button[4]->PUSH = true;
	wait(ms);
	button[4]->PUSH = false;
	wait(500*ms);
	button[1]->PUSH = true;
	wait(ms);
	button[1]->PUSH = false;
	wait(500*ms);
	button[9]->PUSH = true;
	wait(ms);
	button[9]->PUSH = false;
	wait(500*ms);
	button[6]->PUSH = true;
	wait(ms);
	button[6]->PUSH = false;
	wait(500*ms);
	button[8]->PUSH = true;
	wait(ms);
	button[8]->PUSH = false;
	wait(500*ms);
	button[7]->PUSH = true;
	wait(ms);
	button[7]->PUSH = false;
	wait(500*ms);
	button[2]->PUSH = true;
	wait(ms);
	button[2]->PUSH = false;
	wait(500*ms);
	button[5]->PUSH = true;
	wait(ms);
	button[5]->PUSH = false;
	wait(50*ms);
	sc_stop();
	//wait(1000*ms);
	// finger(0); //See function finger(int), which simulates a button being pushed
	// wait(500*ms);
	// finger(3);
	// wait(500*ms);
	// finger(4);
	// wait(500*ms);
	// finger(1);
	// wait(500*ms);
	// finger(9);
	// wait(500*ms);
	// finger(6);
	// wait(500*ms);
	// finger(8);
	// wait(500*ms);
	// finger(7);
	// wait(500*ms);
	// finger(2);
	// wait(500*ms);
	// finger(5);
	// wait(500*ms);

	//sc_stop();
}

}

void top::finger(int btn){ //simulating fingerpush
	button[btn]->PUSH = true;
	cout << "Pushing button number " << btn << endl;
}

int sc_main (int argc , char *argv[])  {
	top top1("Top1");
  	
  	sc_start ();
	return 0;
};