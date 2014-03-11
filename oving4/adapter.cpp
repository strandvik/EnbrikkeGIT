#include "adapter.h"

Adapter::Adapter(sc_module_name name, int addr) : sc_module(name){
	address = addr;
}

void Adapter::pushed(int id){

}

void Adapter::send(int id, int status){
	
}