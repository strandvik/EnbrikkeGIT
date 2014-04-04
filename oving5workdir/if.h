//#include <systemc.h>

#ifndef   	IF_H_
# define   	IF_H_

class FSM_if : virtual public sc_interface {
public:
	virtual void fsm_s() = 0;
	virtual void fsm_t() = 0;
};

#endif 	    /* !IF_H_ */