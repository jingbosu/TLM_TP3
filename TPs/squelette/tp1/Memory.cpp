#include "Memory.h"

Memory::Memory(sc_core::sc_module_name name, size_t size) : sc_core::sc_module(name){
	storage = new ensitlm::data_t[size/sizeof(ensitlm::data_t)];
	size = size;
}

tlm::tlm_response_status Memory::read(ensitlm::addr_t a, ensitlm::data_t& d){
	
	if (a > (4*size)){
		return tlm::TLM_ADDRESS_ERROR_RESPONSE;
	}else{
		d = storage[a/4];
		cout << "je lit : " << d <<". A l'adresse : " << a << endl;
		cout << "Nom du composant: " << name() << endl;	
		return tlm::TLM_OK_RESPONSE;
	}
}

tlm::tlm_response_status Memory::write(ensitlm::addr_t a, ensitlm::data_t d){
	if (a > (4*Memory::size)){
		return tlm::TLM_ADDRESS_ERROR_RESPONSE;
	}else{
		storage[a/4] = d;
		cout << "j’ai recu : " << d <<". A l'adresse : " << a << endl;
		cout << "C'est " << name() <<" qui m'avait donné ces données! " << endl;
		return tlm::TLM_OK_RESPONSE;
	}
}

Memory::~Memory(){
	Memory::size = 0;
	delete Memory::storage;
}
