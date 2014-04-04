#include <systemc.h>
#include "if.h"
#include "statemachine.h"  

const sc_time period (10, SC_NS);
class top : public sc_module{
public:
FSM *fsm;
sc_clock clk;
sc_signal<char> Aout;
sc_signal<bool> Xin;
int Xcount;
int Acount;
bool Xinput;
void testbed();

top (sc_module_name name) : sc_module (name), clk("Clk", period){
	fsm = new FSM("Statemachine", 100, 200); //Creating a new state machine with limit = 100.
	fsm->tick(clk);
	fsm->portA(Aout);
	fsm->X(Xin);

	Xcount = 0;
	Acount = 0;
	Xinput = false;

	SC_HAS_PROCESS(top);
	SC_CTHREAD(testbed, clk);
	}
};

void top::testbed(){
	while(1){
		int intA = rand()%256;
		unsigned char charA = intA;
		Aout.write(charA);
		Acount++;
		if(Xin != Xinput){ 
			Xcount++;
			cout << "X was outputted " << Xcount << " number of times" << endl;
			cout << "A was sent " << Acount << " times." << endl;
		}
		Xinput = Xin;
		wait();
	}
}

int sc_main (int argc , char *argv[])  {
	srand(time(NULL));
	top top1("Top1");
  	sc_start(100, SC_US);
	return 0;
};