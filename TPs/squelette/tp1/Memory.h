#ifndef Memory_H
#define Memory_H

#include "ensitlm.h"
#include "iostream"
using namespace std;

SC_MODULE(Memory) {
	ensitlm::target_socket<Memory> target;
	Memory(sc_core::sc_module_name name, size_t size);
	virtual ~Memory();
	tlm::tlm_response_status read(ensitlm::addr_t a, ensitlm::data_t& d);
	tlm::tlm_response_status write(ensitlm::addr_t a, ensitlm::data_t d);
	ensitlm::data_t * storage;
	size_t size;

};

#endif
