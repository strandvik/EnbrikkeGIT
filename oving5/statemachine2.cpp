#include "statemachine.h"

FSM::FSM(sc_module_name name, int _limit) : sc_module(name){
	limit = _limit;
	InitialState = S0;
	CurrentState = InitialState;
	Xtoggle = false;
	SC_HAS_PROCESS(FSM);
	SC_THREAD(fsm_functionality);
	sensitive << tick;
}


void FSM::fsm_functionality() {
	while(1){
		
		unsigned char portReadA = portA.read();
		int A = portReadA;
		cout << "Recieved on input: " << portReadA << ", or as int: " << A << endl;
		if(A >= limit){
			switch(CurrentState){
				case S0:
					cout << "In state S0. " << endl;
					NextState = S1;
				break;
				case S1:
					cout << "In state S1. " << endl;
					NextState = S2;
				break;
				case S2:
					cout << "In state S2. " << endl;
					Xtoggle = !Xtoggle;
					X->write(Xtoggle);
					NextState = S0;
				break;
					default:
					cout << "Default happend................" << endl;
					NextState = S0;
			}
			CurrentState = NextState;
			wait(tick.posedge_event());
			cout << endl << endl;
		} else{
			NextState = S0;
		}
	}
}