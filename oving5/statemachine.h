#include <systemc.h>

#include "if.h"

class FSM: public sc_module , public FSM_if {
	FSM (sc_module_name name);
	void fsm_functionality;
	sc_in <char> A;
	sc_in <bool> tick;
	sc_out <bool> X;
	virtual void fsm_functionality();

	private:
		enum typeState = {S0, S1, S2};
		typeState = CurrentState, InitialState, NextState;
};