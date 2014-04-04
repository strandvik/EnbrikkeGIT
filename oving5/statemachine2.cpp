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
		//Underneath the substates are nested within a superstate, realized by an if-sentence
		if(A < limit){ //condition for superstate
			NextState = S0;
		}else{ //evaluate substates
			switch(CurrentState){
				case S0:
					if(A >= limit){
						NextState = S1;
					}
				break;
				case S1:
					if(A >= limit){
						NextState = S2;
					}
				break;
				case S2:
					if(A >= limit){
						Xtoggle = !Xtoggle;
						X->write(Xtoggle);
						NextState = S0;
					}
				break;
					default:
					NextState = S0;
			}
		}
		CurrentState = NextState;
	}	
}