#include "ensitlm.h"
#include "bus.h"
#include "Generator.h"
#include "memory.h"
#include "LCDC.h"
#include "ROM.h"
#include "LCDC_registermap.h"
using namespace sc_core;

int sc_main(int argc, char **argv){

	//Instancier les attributs
	Generator Gen("Generator1");
	Bus Bus("Bus");
	// 320*240+10*1024 = 87040 = hex(0x15400)
	Memory Mem("Memory", 87040);
	LCDC LCDC("LCDC",sc_time(1.0/25,SC_SEC));
	sc_signal <bool,SC_MANY_WRITERS>irq_signal("IRQ");
	ROM rom("ROM");
	Bus.initiator.bind(rom.socket);
	//Binding
	Gen.initiator.bind(Bus.target);
	Bus.initiator.bind(Mem.target);

	//LCDC est maitre et esclave a la fois
	LCDC.initiator_socket.bind(Bus.target);
	Bus.initiator.bind(LCDC.target_socket);

	//initialiser l'interruption
	Gen.irq.bind(irq_signal);
	LCDC.display_int.bind(irq_signal);
	
	//Ecriture de bus vers peripheriques
	Bus.map(Mem.target, 0x00000000, 87040);
	Bus.map(LCDC.target_socket, 0x10000000, 12);
	Bus.map(rom.socket, 0x20000000, 38400);
	
	//LCDC
	LCDC.write(LCDC_START_REG, 0x00000001);
	

	
	//ROM
	
	
	sc_core::sc_start();

	return 0;

}