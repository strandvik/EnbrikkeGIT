
#ifndef   	PROCESSOR_H_
# define   	PROCESSOR_H_

#include <systemc.h>
#include "if.h"

const int numberOfProcessors = 100;

class Processor : public sc_module, public processor_if{
public:
  	Processor (sc_module_name name);
	sc_port<processor_if,1,SC_ZERO_OR_MORE_BOUND> up;
	sc_port<processor_if,1,SC_ZERO_OR_MORE_BOUND> down;
	sc_port<processor_if,1,SC_ZERO_OR_MORE_BOUND> left;
	sc_port<processor_if,1,SC_ZERO_OR_MORE_BOUND> right;

	virtual bool free();
	virtual bool test(int);
	virtual bool leftTest(int);
	virtual bool upTest(int);
	virtual	bool rightTest(int);
	virtual void MCU_test();
	virtual void generateRandomNumber();
	sc_signal<bool> test_signal;
	int id, row, collumn;
	bool upConn, leftConn, rightConn, isFree;
	int pos, total;
private:
	sc_mutex process_access;
};

#endif 	    /* !PROCESSOR_H_ */