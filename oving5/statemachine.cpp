#include "statemachine.h"

FSM::FSM(sc_module_name name, int _limit) : sc_module(name){
	limit = _limit;
	InitialState = S0;
	CurrentState = InitialState;
	Xtoggle = false;
	SC_HAS_PROCESS(FSM);
	SC_THREAD(fsm_functionality);
	sensitive << tick.pos();
}


void FSM::fsm_functionality() {
	while(1){
		int A = portA;
		switch(CurrentState){
			case S0:
				cout << "In state S0. " << endl;
				if(A >= limit){
					NextState = S1;
				}else{
					NextState = S0;
				}
			break;
			case S1:
				cout << "In state S1. " << endl;
				if(A < limit){
					NextState = S0;
				}else{
					NextState = S2;
				}
			break;
			case S2:
				cout << "In state S2. " << "A = " << A << ".  And limit" << limit << endl;
				if(A >= limit){
					cout << "Setting Xtoggle" << endl;
					Xtoggle = !Xtoggle;
					X->write(Xtoggle);
					NextState = S0;
				}else if(A < limit){
					NextState = S0;
				}
			break;
				default:
				cout << "Default happend..................................................................." << endl;
				NextState = S0;
		}
		CurrentState = NextState;
		wait(tick->posedge_event());
	}
}