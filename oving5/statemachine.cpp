#include "statemachine.h"

FSM::FSM(sc_module_name name, int _limit) : sc_module(name){
	limit = _limit;
	InitialState = S0;
	CurrentState = InitialState;
	SC_HAS_PROCESS(FSM);
	SC_THREAD(fsm_functionality);
	sensitive << tick;
}


void FSM::fsm_functionality() {
	while(1){
		switch(CurrentState){
			case S0:
				if(A >= limit){
					NextState = S1;
				}else{
					NextState = S0;
				}
			break;
			case S1:

				if(A < limit){
					NextState = S0;
				}else{
					NextState = S2;
				}
			break;
			case S2:
				if(A >= limit){
					X->write(true);
					NextState = S0;
				}else if(A < limit){
					NextState = S0;
				}
			break;
				default:
				NextState = S0;
		}
		CurrentState = NextState;
		wait(tick->posedge_event());
	}
}