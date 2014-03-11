#include "adapter.h"
#define maxMemAdr 0x3FF
#define freeloc 0x00

Adapter::Adapter(sc_module_name name, int addr) : sc_module(name){
	address = addr;
}

// Gets called by the Button when it is pushed.
void Adapter::pushed(int id){
	send(id, 1);
	wait(ms);
	send(id, 0);
	cout << "Button " << id << " has been pushed." << endl;
}

// When a push is made, this one makes a data packet with 3 words.
// 1 with the size, 1 with id and one with the status.
void Adapter::send(int id, int status){
	int packet[3] = {3, id, status};
	int nextFreeAddress;
	adapterToBusPort->burst_read(id, &nextFreeAddress, freeloc, 1, true);
}