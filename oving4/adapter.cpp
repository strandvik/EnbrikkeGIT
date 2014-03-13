#include "adapter.h"

#define FREELOC 0x002C
#define MAX_MEM_ADR 0x102C

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
	adapterToBusPort->burst_read(id, &nextFreeAddress, FREELOC, 1, true);
	if (nextFreeAddress <= FREELOC)
		nextFreeAddress = FREELOC +  4; //First possible address
	else if (nextFreeAddress > (MAX_MEM_ADR - 12))
		nextFreeAddress = FREELOC +  4; // Reseting the round-buffer register.
	adapterToBusPort->burst_write(id, packet, nextFreeAddress, 3, true);
	// Adding the nextFreeAddress and the adapter number into a 4 byte address.
	// And sending it to the Control-register with address 0x0000;
	packet[0] = (nextFreeAddress << 16)|(1<<id);
	nextFreeAddress += 12;
	adapterToBusPort->burst_write(id, &nextFreeAddress, FREELOC, 1, true); //updating the next address in FREELOC
	adapterToBusPort -> burst_write(id, packet, 0x0000, 1, false); //sending to the Control-register.
}
	