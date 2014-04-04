#include "statemachine.h"

FSM::FSM(sc_module_name name, int _limit, int _TimeLimit) : sc_module(name){
	limit = _limit;
	TimeLimit = _TimeLimit;
	InitialState_S = S0;
	CurrentState_S = InitialState_S;
	InitialState_T = T0;
	CurrentState_T = InitialState_T;
	Xtoggle = false;
	tickCounter = 0;
	SC_HAS_PROCESS(FSM);
	SC_THREAD(fsm_s);
	sensitive << tick.pos();

	SC_HAS_PROCESS(FSM);
	SC_THREAD(fsm_t);
	sensitive << tick.pos() << X.value_changed();
}

void FSM::fsm_s() {
	while(1){
		wait(tick.posedge_event());
		unsigned char portReadA = portA.read();
		int A = portReadA;
		//Underneath the substates are nested within a superstate, realized by an if-sentence
		if(A < limit){ //condition for superstate
			NextState_S = S0;
		}else{ //evaluate substates
			switch(CurrentState_S){ // Switch case to evaluate different states
				case S0:
					if(A >= limit){
						NextState_S = S1;
					}
				break;
				case S1:
					if(A >= limit){
						NextState_S = S2;
					}
				break;
				case S2:
					if(A >= limit){
						Xtoggle = !Xtoggle;
						X->write(Xtoggle); // Writing the toggled value of X on outport, to be registered in testbench
						NextState_S = S2; //For task 3
					}
				break;
					default:
					cout << "Default happend................" << endl;
					NextState_S = S0;
			}
		}
	CurrentState_S = NextState_S;
	}	
}

void FSM::fsm_t() {
	while(1){
		wait();
		switch(CurrentState_T){
			case T0:
				if(X.event()){ //When fsm_s outputs X, the event is caught here
					NextState_T = T1;
				}else{
					tickCounter++;
					NextState_T = T0;	
			}
			break;
			case T1:
				ChangeLimit(); //Changes limit according to task 4
				tickCounter = 1;
				NextState_T = T0;
			break;
		}
		CurrentState_T = NextState_T;
	}
}

void FSM::ChangeLimit(){
	if(tickCounter<TimeLimit){
		cout <<"Counted " << tickCounter << " ticks, which is less than Timelimit " << TimeLimit << endl;
		limit++;
		cout << "New limit is " << limit <<  endl << endl;
	}else if(tickCounter>TimeLimit){
		cout <<"Counted " << tickCounter << " ticks, which is greater than Timelimit " << TimeLimit << endl;
		limit--;
		cout << "New limit is " << limit <<  endl << endl;
	}else{
		cout << "Counted ticks equal to timelimit" << endl;
		limit = limit;
		cout << "New limit is still: " << limit <<  endl << endl;

	}
}