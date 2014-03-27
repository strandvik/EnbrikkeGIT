/* -*- mode: c++ -*-*/

#include "control.h"

const int Control::X[9] = {3,8,1,2,9,5,7,6,4};
int Control::nextnumber = 1;


// Constructor
Control::Control (sc_module_name name, int _start_addr, int _end_addr) : sc_module (name){
	start_addr = _start_addr;
	end_addr = _end_addr;
	rawData = 0;
	nextnumber = 0;

	SC_HAS_PROCESS(Control);
	SC_THREAD(mainc);
}

void Control::lights(int id, bool status){
	int buttonOn;
	if(status){
		buttonOn = 2;
		controlOutPort->burst_write(1, &buttonOn, BUTTON_ADDR + id * 4, 1, false);
	}else{
		buttonOn = 0;
		controlOutPort->burst_write(1, &buttonOn, BUTTON_ADDR + id * 4, 1, false);
	}
}

void Control::clearButtonLights(){
	for(int i = 1; i < 10; i++){
		lights(i, false);
	}
	cout << "All lights cleared" << endl << endl << endl;

}

void Control::pushed(int id){
	if(id == 0) {
		clearButtonLights();
		nextnumber = 1;
		cout << "System started" << endl << endl;
	}else if(X[id-1] == nextnumber){ //Spilleren traff riktig knapp
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

void Control::mainc(){
	int buttonInfo[3];
	while(true){
		int status = rawData & 0x0FFF; // this will remove all the address bits
		int address = (rawData >> 16 ); //Shifting the adresses into address
		if(status){ //if a change is made in the status variable, we check which position is set to 1.
			int k = 0;
			for (int i = 0; i < 10; ++i)
			{
				k = status >> i;
				if(k&1){
					controlOutPort->burst_read(1, buttonInfo, address, 3, false);
					if(buttonInfo[2] != 0){ //Status != 0, its pushed.
						pushed(i);
						break;
					}else{
						cout << "Button " << i << " released" << endl << endl;
						break;
					}
				}
			}
		}
		rawData = 0; // resetting register
		status = 0;
		address = 0;
		wait(1000*ns);
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
