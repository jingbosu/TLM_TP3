#include "ensitlm.h"
#include "bus.h"
#include "Generator.h"
#include "Memory.h"


int sc_main(int argc, char **argv){

	Generator Gen("Generator1");
	Bus Bus("Bus");
	Memory Mem("Memory", 32);
	Gen.initiator.bind(Bus.target);
	Bus.initiator.bind(Mem.target);

	Bus.map(Mem.target, 0x10000000, 256);
	
	sc_core::sc_start();


	return 0;

}
