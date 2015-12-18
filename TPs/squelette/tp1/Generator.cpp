#include "Generator.h"

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name)
{
	SC_THREAD(geneCom);

}

void Generator::geneCom()
{
	ensitlm::addr_t addr_store = 0x10000000;
	for (int i =0; i < 10; i++){
		initiator.write(addr_store, i);
		addr_store+=4;
	}
	
	ensitlm::addr_t addr_read = 0x10000000;
	ensitlm::data_t data_read = 0;
	for (int i =0; i < 10; i++){
		initiator.read(addr_read, data_read);
		addr_read+=4;
	}

}

