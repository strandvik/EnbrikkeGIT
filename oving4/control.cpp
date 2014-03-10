/* -*- mode: c++ -*-*/

#include "control.h"

const int Control::X[9] = {3,8,1,2,9,5,7,6,4};
int Control::nextnumber = 1;


// Constructor
Control::Control (sc_module_name name) : sc_module (name){}

void Control::clearButtonLights(){
	for(int i = 0; i < 10; i++){
		controlOutPort->lights(false, i);
	}
	wait(ctrl_delay);
	cout << "All lights cleared" << endl << endl << endl;
}

void Control::pushed(int id){
	while(control_access.trylock() != 0){	
		wait(ctrl_mutex_delay);
	}	
	control_access.lock();
	wait(ctrl_delay);
	if(id == 0) {
		clearButtonLights();
		nextnumber = 1;
		cout << "System started" << endl << endl;
	}else if(X[id-1] == nextnumber){ //Spilleren traff riktig knapp, beskjed om
		controlOutPort->lights(true, id); 
		++nextnumber;//neste riktige nummer inkrementeres.
		if(nextnumber == 10){
			cout<< "All lights on" << " You won! AWESOMENESS" << endl;
 		}	
	}else if(X[id-1] != nextnumber){ //Spillet skal resettes.
		cout << endl << id << " is WRONG, you suck!" << endl;
		nextnumber = 1;
		clearButtonLights();
	}
	control_access.unlock();	
}
