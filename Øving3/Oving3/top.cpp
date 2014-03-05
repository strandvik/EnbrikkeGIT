#include <systemc.h>
#include <string>
#include "if.h"
#include "processor.h"

using namespace std;

const sc_time ms (1, SC_MS);
class top : public sc_module {
public:
	virtual void testbed();
	Processor* procarray[100];
	top (sc_module_name name, int numberOfProcessors) : sc_module (name){
		char buf[20];
		for (int i = 0; i < numberOfProcessors; ++i){
			sprintf(buf, "MCUinst%d\0", i);
			procarray[i] = new Processor(buf);
		}
		int row = 0;
		int nSqrt = sqrt(numberOfProcessors);
		int lastRow = nSqrt-1;
		cout << "Connecting processor array: " << endl;//Underneath the code for connecting the different processors
		for (int i = 0; i < numberOfProcessors; i++){ 
			procarray[i]->pos = i;
			procarray[i]->total = numberOfProcessors;
			procarray[i]->isFree = false;
			// Connection upwards:
			if (row != 0){
				procarray[i]->up(*procarray[i-nSqrt]);
				cout << i << " connected upwards to " << i-nSqrt << endl;
			}
			// Connection downwards:
			if (row != lastRow){
				procarray[i]->down(*procarray[i+nSqrt]);
				cout << i << " connected downwards to " << i+nSqrt << endl;
			}
			// Connection left:
			if (i % nSqrt != 0){
				procarray[i]->left(*procarray[i-1]);
				cout << i << " connected left to " << i-1 << endl;
			}
			//Connection right:
			if (i % nSqrt != nSqrt - 1){
				procarray[i]->right(*procarray[i+1]);
				cout << i << " connected right to " << i+1 << endl;
			} else
				row++;
		}
		SC_HAS_PROCESS(top);
		SC_THREAD(testbed);
	}

};

void top::testbed(){
	wait(1000*ms); 
	for (int i = 0; i < numberOfProcessors; i++){
		//int tmp = rand()%numberOfProcessors;
		procarray[i]->test_signal = true;
		cout << "Testing for procarray[" << i << "] with id: " << procarray[i]->id << endl;
		wait(500*ms); 
	}
	wait(5000*ms);
	for (int i = 0; i < numberOfProcessors; ++i){
		cout << "Processor number " << i << " ended up with id: " << procarray[i]->id << endl;
	}
}

int sc_main (int argc , char *argv[])  {
  	srand(time(NULL));
	top top1("Top1", 100);
  	sc_start ();
	return 0;
};		