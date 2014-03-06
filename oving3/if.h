//** if.h
#ifndef   	IF_H_
# define   	IF_H_
// Interface for Processor
class processor_if:  virtual public sc_interface {
	public:
		virtual bool free() = 0;
		virtual bool test(int) = 0;
		virtual bool leftTest(int) = 0;
		virtual bool rightTest(int) = 0;
		virtual bool upTest(int) = 0;
		virtual void MCU_test() = 0;
		virtual void generateRandomNumber() = 0;
};

#endif 	    /* !IF_H_ */
