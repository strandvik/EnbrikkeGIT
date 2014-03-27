#include <systemc.h>

#include "if.h"
#include "statemachine.h"

const sc_time period (10, SC_NS);
class top : public sc_module{

FSM *fsm;
sc_clock clk;
sc_out<char> Aout;
sc_in<bool> Xin;

//char sendA;
void testbed();

top (sc_module_name name) : sc_module (name), clk("Clk", period){
	fsm = new FSM("Statemachine", 100);
	fsm->tick(clk);
	fsm->A(Aout);
	fsm->X(Xin);
	SC_HAS_PROCESS(top);
	SC_THREAD(testbed);
}
};

void top::testbed(){
	while(1){
		char tmpA = rand()%256;
		Aout->tmpA;

	}


}

int sc_main (int argc , char *argv[])  {
	srand(time(NULL));
	top top1("Top1");
  	
  	sc_start ();
	return 0;
};