/********************************************************************
 * Copyright (C) 2009, 2012 by Verimag                              *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

/*!
  \file hal.h
  \brief Harwdare Abstraction Layer : implementation for MicroBlaze
  ISS.


*/
#ifndef HAL_H
#define HAL_H

#include <stdint.h>


/* Dummy implementation of abort(): dereference a NULL pointer */
#define abort() ((*(int *)NULL) = 0)

/* TODO : implementer ces primitives pour la compilation croisée */
#define read_mem(a)     (*(uint32_t*)(a))
#define write_mem(a,d)  (*(uint32_t*)(a) = (uint32_t)(d))
#define wait_for_irq()  abort()
#define cpu_relax()     abort()

//volatile uint32_t read_mem(uint32_t addr) {
//	return *(uint32_t*)addr;
//}

//volatile void write_mem(uint32_t addr, uint32_t data) {
//	*(uint32_t*)addr = data;
//}

/* printf is implemented with just one argument, A TESTER!!!!!!
	UART_BASEADDR peut trouver dans address_map.h
	UART_FIFO_WRITE peut trouver dans hardware/offsets/uart.h
*/
#define printf(x) int i = 0;\
		  for(i = 0; x[i] != '\0'; i++){ \
		  	(*(char*)(UART_BASEADDR + UART_FIFO_WRITE)) = ((char)x[i]);\
		  }

#endif /* HAL_H */
