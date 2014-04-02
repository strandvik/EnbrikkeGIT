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
		wait(tick.posedge_event());
		unsigned char portReadA = portA.read();
		int A = portReadA;
		cout << "Recieved on input: " << portReadA << ", or as int: " << A << endl;
		switch(CurrentState){
			case S0:
				cout << "In state S0. " << endl;
				if(A >= limit){
					cout << A << " > " << limit << " nextstate = S1" << endl;
					NextState = S1;
				}else{ //if A < limit we stay in S0
					cout << A << " < " << limit << " nextstate = S0" << endl;
					NextState = S0;
				}
			break;
			case S1:
				cout << "In state S1. " << endl;
				if(A >= limit){
					cout << A << " > " << limit << " nextstate = S2" << endl;
					NextState = S2;
				}else{
					cout << A << " < " << limit << " nextstate = S0" << endl;
					NextState = S0;
				}
			break;
			case S2:
				cout << "In state S2. " << endl;
				if(A >= limit){
					cout << A << " > " << limit << " nextstate = S0" << endl;
					Xtoggle = !Xtoggle;
					X->write(Xtoggle);
					NextState = S0;
				}else if(A < limit){
					cout << A << " < " << limit << " nextstate = S0" << endl;
					NextState = S0;
				}
			break;
				default:
				cout << "Default happend................" << endl;
				NextState = S0;
		}
		CurrentState = NextState;
		cout << endl << endl;
	}
}