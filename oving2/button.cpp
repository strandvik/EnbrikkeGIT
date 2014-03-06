/* -*- mode: c++ -*-
** button.cpp
** 
** Made by Kjetil Svarstad
** 
*/

#include "button.h"

// Functionality for the Button class

// Constructor
Button::Button (sc_module_name name, int _id) : sc_module (name)
{
  // Constructor code	
	id = _id;	
	SC_HAS_PROCESS(Button);		
	SC_THREAD(main);
	//sensitive << PUSH;

}
void Button::lights(bool lightStat){
	if (lightStat == true){
		finishtime = sc_time_stamp();
		cout << endl << "Light number "  << id << " is on!" << endl << "The push and calculate process took: "<< finishtime - pushtime <<endl <<endl;
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
		cout << id << " Was pushed";
		buttonOutPort->pushed(id);
		}
	}
}
