/* -*- mode: c++ -*-

** All interfaces collected here
*/

#ifndef   	IF_H_
# define   	IF_H_

const sc_time ps (1, SC_PS);
const sc_time ns (1, SC_NS);
const sc_time ms (1, SC_MS);
// Interface for Button
class Button_if:  virtual public sc_interface {
	public:
		virtual void lights(bool) = 0;			
};

// Interface for Control
class Control_if: virtual public sc_interface {
	public:
		virtual void pushed(int) = 0;				
};

class Adapter_if: virtual public sc_interface {
	public:
		virtual void pushed(int) = 0;
	
};

// Proxy-interface for Bus to Button
class bus_push_if: virtual public sc_interface {
	public:
		virtual void pushed (int) = 0;
};

class bus_light_if: virtual public sc_interface{
	public:
		virtual void lights(bool, int) = 0;
};


#endif 	    /* !IF_H_ */
