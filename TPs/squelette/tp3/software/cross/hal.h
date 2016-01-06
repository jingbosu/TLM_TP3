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

/* Read and write in memory */
#define read_mem(a)     (*(volatile uint32_t*)(a))
#define write_mem(a,d)  (*(volatile uint32_t*)(a) = (uint32_t)(d))

#define wait_for_irq()  abort()
#define cpu_relax()     abort()

/* printf is implemented with just one argument
*  UART_BASEADDR can be found in address_map.h
*  UART_FIFO_WRITE can be found in hardware/offsets/uart.h
*  On ecrit une chaine de caracteres jusqu'on trouve le symbol 
*  '\0' qui represente la fin de string
*/

#define printf(x) \
		do {\
			int i = 0;\
			for(i = 0; x[i] != '\0'; i++) { \
			  	(*(volatile uint32_t*)(UART_BASEADDR + UART_FIFO_WRITE)) = ((uint32_t)x[i]);\
			} \
		} while(0)

#endif /* HAL_H */
