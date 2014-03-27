#include "statemachine.h"


void FSM::fsm_functionality() {
	Switch(CurrentState){
		case S0:
		if(pos_edge(tick)){
			if(A >= limit){
				NextState = S1;
			}
		}
		break;

		case S1:
		if(pos_edge(tick)){
			if(A < limit){
				NextState = S0;
			}else{
				NextState = S2;
			}
		}
		break;

		case S2:
		if(pos_edge(tick)){
			if(A >= limit){
				X->true;
			}
		}
	}



}
