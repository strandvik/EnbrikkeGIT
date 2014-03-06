//** processor.cpp

#include "processor.h"
// Functionality for the Processor class
const sc_time mutexdelay(50, SC_NS);
const sc_time startupdelay(200, SC_NS);
const sc_time MS(1, SC_MS);

// Constructor
Processor::Processor (sc_module_name name) : sc_module (name){
	generateRandomNumber(); //Generating random id for the processor
	SC_HAS_PROCESS(Processor);
	SC_THREAD(MCU_test);
}

//if there's a connection to the up and the function to the up is available.
//then test
bool Processor::upTest(int number){
	if (upConn){
		while(!(up->free())){
			wait(10*MS);
		}
		return up->test(number);
	} else
		return false;
}

//if there's a connection to the left and the function to the left is available.
//then test
bool Processor::leftTest(int number){
	if (leftConn){
		while(!(left->free())){
			wait(10*MS);
		}
		return left->test(number);
	} else 
		return false;
}

//if there's a connection to the right and the function to the right is available.
//then test
bool Processor::rightTest(int number){
	if (rightConn){
		while(!(right->free())){
			wait(10*MS);
		}
		return right->test(number);
	} else 
		return false;
}

//checking if someone else is using the MCU
bool Processor::free(){
	while(process_access.trylock() != 0){
		cout << "Processor " << id << " is waiting on mutex." << endl;
		wait(mutexdelay);
	}
	process_access.lock(); //Using mutex to prevent multiple processors setting the isFree flag at once.
	if(isFree){
		isFree = false; //setting a busy flag for other processors to see
		process_access.unlock();
		return true; //Telling processor its available for testing
	}
	else{
		process_access.unlock();
		return false; //not available for testing
	}
}

//returns true if the number exists either here, up or to the left.
bool Processor::test(int number){ 
	if (id == number){
		return true;
	}else if (pos == 0){
		return false;
	}else if (!(row%2) && collumn != 0){
		return leftTest(number);
	} else if (!(row%2) && collumn == 0){
		return upTest(number);
	} else if((row%2) && (collumn == (sqrt(total)-1))){
		return upTest(number);
	}else if(row%2 && collumn != (sqrt(total)-1)){
		return rightTest(number);
	}
}

void Processor::generateRandomNumber(){ //Function that sets a new
	id = rand()%numberOfProcessors;
}

void Processor::MCU_test(){
	generateRandomNumber();
	row = pos / sqrt(total);
	collumn = pos% (int)sqrt(total);
	upConn = up.get_interface(); // Checks the connection upwards, 0 = unconnected
	leftConn = left.get_interface();// Checks the connection left, 0 = unconnected
	rightConn = right.get_interface();// Checks the connection left, 0 = unconnected
	bool exists = false;
	wait(test_signal.value_changed_event());
	if (pos == 0){
		cout << "pos 0 is free!!!!!" << endl;
		isFree = true;
		cout << isFree;
	}else if (!(row%2) && collumn != 0){
		cout << "Processor " << pos << " running left tests with id " << id << endl;
		exists = leftTest(id);
		while(exists){
			generateRandomNumber();
			cout << "Processor " << pos << " still running left tests with id " << id << endl;
			exists = leftTest(id);
			
		}
		cout << "pos " << pos << " is free!!!!!" << endl;
	} else if (!(row%2) && collumn == 0){
		exists = upTest(id);
		while(exists){
			generateRandomNumber();
			exists = upTest(id);
			cout << "Processor " << pos << " still running up tests with id " << id << endl;
		}
		cout << "pos " << pos << " is free!!!!!" << endl;
	} else if(row%2 && (collumn == (sqrt(total)-1))){
		exists = upTest(id);
		while(exists){
			generateRandomNumber();
			exists = upTest(id);
			cout << "Processor " << pos << " still running up tests with id " << id << endl;
		}
		cout << "pos " << pos << " is free!!!!!" << endl;
	}else if(row%2 && collumn != (sqrt(total)-1)){
		exists = rightTest(id);
		while(exists){
			generateRandomNumber();
			exists = rightTest(id);
			cout << "Processor " << pos << " still running right tests with id " << id << endl;
		}
		cout << "pos " << pos << " is free!!!!!" << endl;
	}
	isFree = true;
}