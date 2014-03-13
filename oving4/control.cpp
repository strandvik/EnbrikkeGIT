/* -*- mode: c++ -*-*/

#include "control.h"

const int Control::X[9] = {3,8,1,2,9,5,7,6,4};
int Control::nextnumber = 1;


// Constructor
Control::Control (sc_module_name name) : sc_module (name){}

void Control::lights(int id, bool status){
	int buttonInfo[3] = {3, 11, status};
	controlOutPort->burst_write(1, buttonInfo, BUTTON_ADDRESS + id * 4, 3, true);
}

void Control::clearButtonLights(){
	for(int i = 0; i < 10; i++){
		lights(i, false);
	}
	wait(ctrl_delay);
	cout << "All lights cleared" << endl << endl << endl;
}

void Control::pushed(int id){
	if(id == 0) {
		clearButtonLights();
		nextnumber = 1;
		cout << "System started" << endl << endl;
	}else if(X[id-1] == nextnumber){ //Spilleren traff riktig knapp, beskjed om
		lights(i, true); 
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
	unsigned int rawData;
	int buttonInfo[3];
	while(true){
		controlOutPort->direct_read(&rawData, CONTROL_ADDRESS);
		unsigned int status = rawData & 0x0000FFFF;
		unsigned int address = rawData & 0xFFFF0000;
		address = address >> 16;
		if(status){
			controlOutPort->burst_read(1, &buttonInfo, address, 1, true);
			if(buttonInfo[2] == 1){
				pushed(buttonInfo[1]);
			}
		}
		wait(10*ns);
	}

}