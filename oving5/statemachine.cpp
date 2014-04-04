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
		switch(CurrentState){
			case S0:
				if(A >= limit){
					NextState = S1;
				}else{ //if A < limit we stay in S0
					NextState = S0;
				}
			break;
			case S1:
				if(A >= limit){
					NextState = S2;
				}else{
					NextState = S0;
				}
			break;
			case S2:
				if(A >= limit){
					Xtoggle = !Xtoggle;
					X->write(Xtoggle);
					NextState = S0;
				}else if(A < limit){
					NextState = S0;
				}
			break;
				default:
				NextState = S0;
		}
		CurrentState = NextState;
	}
}