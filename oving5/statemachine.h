#include <systemc.h>

#include "if.h"

class FSM: public sc_module , public FSM_if {
	public:
		
	FSM (sc_module_name name, int _limit);
	sc_in <char> portA;
	sc_in <bool> tick;
	sc_out <bool> X;
	virtual void fsm_functionality();

	private:
		int limit;
		int count;
		bool Xtoggle;
		bool Xcompare;
		enum typeState {S0, S1, S2, T0, T1};
		typeState  CurrentState, InitialState, NextState, CurrentStateT, InitialStateT, NextStateT;
};

//http://hvg.ece.concordia.ca/Publications/TECH_REP/FSMSC_TR07/TR-FSM-SystemC.pdf