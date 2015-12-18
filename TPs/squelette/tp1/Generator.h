#ifndef Generator_H
#define Generator_H

#include "ensitlm.h"
#include <iostream>

using namespace std;
SC_MODULE(Generator) {
	ensitlm::initiator_socket<Generator> initiator;
	
	Generator(sc_core::sc_module_name name);

	SC_HAS_PROCESS(Generator);
	void geneCom();
};

#endif
