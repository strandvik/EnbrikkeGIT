/* -*- mode: c++ -*-*/

#include "control.h"

const int Control::X[9] = {3,8,1,2,9,5,7,6,4};
int Control::nextnumber = 1;


// Constructor
Control::Control (sc_module_name name, int _start_addr, int _end_addr) : sc_module (name){
	start_addr = _start_addr;
	end_addr = _end_addr;
	rawData = 0;

	SC_HAS_PROCESS(Control);
	SC_THREAD(main);
}

void Control::lights(int id, bool status){
	int buttonInfo[3] = {3, status, status};
	controlOutPort->burst_write(1, buttonInfo, BUTTON_ADDR + id * 4, 3, true);
}

void Control::clearButtonLights(){
	for(int i = 0; i < 10; i++){
		lights(i, false);
	}
	wait(10*ns);
	cout << "All lights cleared" << endl << endl << endl;
}

void Control::pushed(int id){
	if(id == 0) {
		clearButtonLights();
		nextnumber = 1;
		cout << "System started" << endl << endl;
	}else if(X[id-1] == nextnumber){ //Spilleren traff riktig knapp, beskjed om
		lights(id, true); 
		++nextnumber;//neste riktige nummer inkrementeres.
		if(nextnumber == 10){
			cout<< "All lights on" << " You won! AWESOMENESS" << endl;
 		}	
	}else if(X[id-1] != nextnumber){ //Spillet skal resettes.
		cout << endl << id << " is WRONG, you suck!" << endl;
		nextnumber = 1;
		clearButtonLights();
	}
}

void Control::main(){
	pushed(0);
	int buttonInfo[3];
	cout << "Starting up main" << endl;
	while(true){
		controlOutPort->burst_read(1, &rawData, CONTROL_ADDRESS, 1, false);
		unsigned int status = rawData & 0x0000FFFF;
		unsigned int address = rawData & 0xFFFF0000;
		address = address >> 16;
		if(status){
			controlOutPort->burst_read(1, buttonInfo, address, 1, false);
			if(buttonInfo[2] != 0){
				pushed(buttonInfo[1]);
			}
		}
		wait(10*ns);
	}

}

//Functionality for handling read and write calls, and addressing.
simple_bus_status Control::read(int *data, unsigned int address){
	*data = rawData;
	return SIMPLE_BUS_OK;
}
simple_bus_status Control::write(int *data, unsigned int address){
	rawData = *data;
	return SIMPLE_BUS_OK;
}
bool Control::direct_read(int *data, unsigned int address){
	read(data,address);
	return true;
}
bool Control::direct_write(int *data, unsigned int address){
	write(data,address);
	return true;
}
unsigned int Control::start_address() const {
    return start_addr;
}
unsigned int Control::end_address() const {
    return end_addr;
}
