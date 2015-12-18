#include "Generator.h"
#include "LCDC_registermap.h"
Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name)
{
	SC_THREAD(geneCom);
	
	SC_METHOD(interrputCom);
	sensitive <<irq.pos();
}

void Generator::geneCom()
{
	ensitlm::addr_t addr_mem = 0x00000000;
	ensitlm::addr_t addr_LCDC = 0x10000000;
	ensitlm::addr_t addr_rom = 0x20000000;
	ensitlm::data_t data_rom;
	ensitlm::data_t w,x,y,z;
	
	int32_t offset = 0;
	int decalage = 11;
	//for(int i = 0; i<IMG_SIZE/4; i++){
	//	initiator.write(addr_mem, 0xFFFFFFFF);
	//	addr_mem+=4;
	//}
	while(true){
		for (int i=0; i<(38400/4);i++){
			//read 8 pixels
			initiator.read(addr_rom, data_rom);
			ensitlm::data_t data_final = 0x00000000;
			ensitlm::data_t temp = 0x00000000;
			bool n = false;
			
			for (int j = 0; j<2; j++){
				if (!n) {
					temp = (data_rom & 0xFFFF0000)>>16;
					n = true;
				} else {
					temp = (data_rom & 0x0000FFFF);
				}
				
				w = (0x000F & temp) << 4;
				x = (0x00F0 & temp) << 8;
				y = (0x0F00 & temp) << 12;
				z = (0xF000 & temp) << 16;

				data_final = w+x+y+z;
				offset=(addr_mem+320*(decalage-1))%(320*240);
				initiator.write(offset, data_final);
				addr_mem+=4;
			}
			addr_rom+=4;
		}
 		decalage = (decalage+1)%240;
		wait(irq_eve);
		initiator.write(addr_LCDC+LCDC_INT_REG, 0x00000000);
		addr_mem = 0x00000000;
		addr_rom = 0x20000000;
	}

}
void Generator::interrputCom(){
	cout<<"Voila j'ai fini"<<endl;
	irq_eve.notify();
}
