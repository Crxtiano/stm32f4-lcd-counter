/*
 * stm32f4xx.h
 *
 *  Created on: Aug 27, 2025
 *      Author: Benoit Christian Mbole Zogo
 */

#ifndef STM32F4XX_H_
#define STM32F4XX_H_

#include <stdint.h>

/*===============RCC================*/
#define RCC_BASE			0x40023800UL
#define RCC					((RCC_TypeDef *) RCC_BASE)

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;		//offset 0x30
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t RESERVED6[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
} RCC_TypeDef;

#define RCC_AHB1ENR_GPIODEN		(1 << 3)

/*=========GPIOD==============*/
#define GPIOD_BASE		0x40020C00UL
#define GPIOD			((GPIO_TypeDef *) GPIOD_BASE)

typedef struct {
	volatile uint32_t MODER;	//mode register
	volatile uint32_t OTYPER;	//output type
	volatile uint32_t OSPEEDR;	//speed
	volatile uint32_t OSPUPDR;	//pull-up/pull-down
	volatile uint32_t IDR;		//input data
	volatile uint32_t ODR;		//output data
	volatile uint32_t BSRR;		//bit set/reset
	volatile uint32_t LCKR;
	volatile uint32_t AFRL[2];	//alternate function
} GPIO_TypeDef;


#endif /* STM32F4XX_H_ */
