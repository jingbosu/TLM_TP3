#include "ensitlm.h"
#include "native_wrapper.h"
using namespace std;
/* extern "C" is needed since the software is compiled in C and
 * is linked against native_wrapper.cpp, which is compiled in C++.
 */
extern "C" int __start();
extern "C" void __interrupt();

extern "C" void write_mem(uint32_t addr, uint32_t data) {
	NativeWrapper::get_instance()->write_mem(addr, data);
}

extern "C" unsigned int read_mem(uint32_t addr) {
	return NativeWrapper::get_instance()->read_mem(addr);
}

extern "C" void cpu_relax() {
	NativeWrapper::get_instance()->cpu_relax();
}

extern "C" void wait_for_irq() {
	NativeWrapper::get_instance()->wait_for_irq();
}

/* To keep it simple, the soft wrapper is a singleton, we can
 * call its methods in a simple manner, using
 * NativeWrapper::get_instance()->method_name()
 */
NativeWrapper * NativeWrapper::get_instance() {
	static NativeWrapper * instance = NULL;
	if (!instance)
		instance = new NativeWrapper("native_wrapper");
	return instance;
}

NativeWrapper::NativeWrapper(sc_core::sc_module_name name) : sc_module(name),
							     irq("irq")
{
	SC_THREAD(compute);
	
	SC_METHOD(interrupt_handler_internal);
        sensitive << irq.pos();
	dont_initialize();       
}

void NativeWrapper::write_mem(unsigned int addr, unsigned int data)
{
	tlm::tlm_response_status status;
	status = socket.write(addr, data);
	if(status != tlm::TLM_OK_RESPONSE){
		cout << "Can't write correctly!" << endl;
		abort();
	}
}

unsigned int NativeWrapper::read_mem(unsigned int addr)
{
	unsigned int data;
	tlm::tlm_response_status status;
	status = socket.read(addr, data);
	if(status != tlm::TLM_OK_RESPONSE){
		cout << "Can't read correctly!" << endl;
		abort();
	}
	return data;
}

void NativeWrapper::cpu_relax()
{
	wait(1, sc_core::SC_MS);
}

void NativeWrapper::wait_for_irq()
{
	if(!interrupt) {
		wait(interrupt_event);
	}
	interrupt = false;
}

void NativeWrapper::compute()
{
	__start();
}

void NativeWrapper::interrupt_handler_internal()
{
	interrupt = true;
	interrupt_event.notify();
	__interrupt();
}
