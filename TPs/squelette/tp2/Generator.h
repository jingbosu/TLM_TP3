#ifndef Generator_H
#define Generator_H

#include "ensitlm.h"
#include "LCDC_registermap.h"

#include <iostream>
using namespace std;
using namespace sc_core;
#define IMG_SIZE 76800
#define RAM_addr 0x00000000
#define LCDC_addr 0x10000000
#define ROM_addr 0x20000000
SC_MODULE(Generator) {
	ensitlm::initiator_socket<Generator> initiator;
	sc_core::sc_in<bool> irq;
	Generator(sc_core::sc_module_name name);

	SC_HAS_PROCESS(Generator);
	
	void attente_irq();
	void geneCom();
	void interrputCom();
	sc_core::sc_event irq_eve;
};

#endif
