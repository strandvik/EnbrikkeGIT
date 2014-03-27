/* -*- mode: c++ -*-
** button.cpp
*/
#include "button.h"

Button::Button (sc_module_name name, int _id) : sc_module (name){	
	id = _id;	
	SC_HAS_PROCESS(Button);		
	SC_THREAD(main);
}
void Button::lights(bool lightStat){
	if (lightStat == true){
		finishtime = sc_time_stamp();
		cout << endl << "Light number "  << id << " is on!" << endl << "The push and calculate process took: "<< finishtime - pushtime <<endl;
		light = true;
	}else if(lightStat == false){
		finishtime = sc_time_stamp();
		cout << endl << "Light number "  << id << " is off!" <<endl << "The push and calculate process took: "<< finishtime - pushtime <<endl;
		light = false;
	}
}

void Button::main(){
	while(true){
		wait(PUSH.value_changed_event());
		if(PUSH == true){
		pushtime = sc_time_stamp();
		cout << "Button " << id << " was pushed";
		buttonToAdapterPort->pushed(id);
		}
		wait(ps);
	}
}
