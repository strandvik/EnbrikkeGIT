#include "statemachine.h"

FSM::FSM(sc_module_name name, int _limit) : sc_module(name){
	limit = _limit;
	count = 0;
	InitialState = S0;
	InitialStateT = T0;
	CurrentStateT = InitialStateT;
	CurrentState = InitialState;
	Xtoggle = false;
	Xcompare = false;
	SC_HAS_PROCESS(FSM);
	SC_THREAD(fsm_s);
	sensitive << tick;
}


void FSM::fsm_s() {
	while(1){
		wait(tick.posedge_event());
		unsigned char portReadA = portA.read();
		int A = portReadA;
		cout << "Recieved on input: " << portReadA << ", or as int: " << A << endl;
		//Underneath the substates are nested within a superstate, realized by an if-sentence
		if(A < limit){ //condition for superstate
			cout << A << " < " << limit << " nextstate = S0" << endl;
			NextState = S0;
		}else{ //evaluate substates
			switch(CurrentState){
				case S0:
					cout << "In state S0. " << endl;
					if(A >= limit){
						cout << A << " > " << limit << " nextstate = S1" << endl;
						NextState = S1;
					}
				break;
				case S1:
					cout << "In state S1. " << endl;
					if(A >= limit){
						cout << A << " > " << limit << " nextstate = S2" << endl;
						NextState = S2;
					}
				break;
				case S2:
					cout << "In state S2. " << endl;
					if(A >= limit){
						cout << A << " > " << limit << " nextstate = S2" << endl;
						Xtoggle = !Xtoggle;
						X->write(Xtoggle);
						NextState = S2; //For task 3
					}
				break;
					default:
					cout << "Default happend................" << endl;
					NextState = S0;
			}
			switch(CurrentStateT){
				case T0:
					if (Xcompare != Xtoggle){
						Xcompare = Xtoggle;
						NextStateT = T1;
					} else {
						NextStateT = T0;
						counter ++;
					}
				break;
				case T1:
					cout << "Should we just print that the limit is changed" << endl;
					cout << " or whould we connect it like with line 49?" << endl;
					cout << "The limit had been changed " << endl;
					count = 1;
					NextStateT = T0;
				break;
			}
		}
		CurrentState = NextState;
		cout << "Updated state to "<< CurrentState << endl << endl;	
	}	
}