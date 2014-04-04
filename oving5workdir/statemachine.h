#include <systemc.h>

#include "if.h"

class FSM: public sc_module , public FSM_if {
	public:
		
	FSM (sc_module_name name, int _limit,int _TimeLimit);
	sc_in <char> portA;
	sc_in <bool> tick;
	sc_out <bool> X;
	virtual void fsm_s();
	virtual void fsm_t();
	void ChangeLimit();

	private:
		int limit;
		int TimeLimit;
		int tickCounter;
		bool Xtoggle;
		enum typeStateS {S0, S1, S2};
		typeStateS  CurrentState_S, InitialState_S, NextState_S;
		enum typeStateT {T0, T1};
		typeStateT  CurrentState_T, InitialState_T, NextState_T;
};

//http://hvg.ece.concordia.ca/Publications/TECH_REP/FSMSC_TR07/TR-FSM-SystemC.pdf