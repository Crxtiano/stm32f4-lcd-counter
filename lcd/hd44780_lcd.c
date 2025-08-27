/*
 * hd44780_lcd.c
 *
 *  Created on: Aug 27, 2025
 *      Author: Benoit Christian Mbole Zogo
 */
#include "stm32f4xx.h"
#include "hd44780_lcd.h"
#include <stdint.h>
#include <string.h>

// Internal help functions
static void lcd_enable_pulse(void);			// Send pulse to E (signal for reading)
static void lcd_send_4bits(uint8_t data);	// Send 4-bit data
static void delay(volatile uint32_t time);	// Simple delay function

void lcd_init(void)
{
	//Enable clock
	LCD_RCC_ENR_REG |= RCC_AHB1ENR_GPIODEN;

	// Configure pins as output (each pin has 2 bits in the MODER register)
	LCD_GPIO_BASE ->MODER |= (1 << (LCD_PIN_RS * 2)) |
							 (1 << (LCD_PIN_E * 2)) |
							 (1 << (LCD_PIN_D4 * 2)) |
							 (1 << (LCD_PIN_D5 * 2)) |
							 (1 << (LCD_PIN_D6 * 2)) |
							 (1 << (LCD_PIN_D7 * 2));
	delay(50000);	// Waiting time after switching on

	// Initialization sequence for HD44780 in 4-bit mode
	lcd_send_4bits(0x03);
	delay(5000);
	lcd_send_4bits(0x03);
	delay(5000);
	lcd_send_4bits(0x03);
	delay(5000);
	lcd_send_4bits(0x02);	// Switch to 4-bit mode

	// Configuration of the display
	lcd_send_cmd(0x28);		// Function Set: 4-bit, 2 lines, 5x8 dots
	lcd_send_cmd(0x0c);		// Display ON, Cursor OFF
	lcd_send_cmd(0x06);		// Cursor to the right, no display shift
	lcd_clear();			// Clear display
}

void lcd_clear(void) {
	lcd_send_cmd(0x01);	// Clear Display
	delay(2000);		// Waiting time until LCD is ready
}

void lcd_put_cur(uint8_t row, uint8_t col){
	// Calculate address for cursor position
	uint8_t addr = (row == 0) ? col : 0x40 + col;
	lcd_send_cmd(0x80 | addr);	// Set DDRAM address
}

void lcd_send_string(char *str){
	// Send individual characters of the string
	while(*str) {
		lcd_send_data(*str++);
	}
}

void lcd_send_cmd(uint8_t cmd){
	// RS = 0 -> Command
	LCD_GPIO_BASE ->BSRR = (1 << (LCD_PIN_RS + 16));	// Clear RS
	lcd_send_4bits(cmd >> 4);							// Send high nibble
	lcd_send_4bits(cmd & 0x0F);							// Send low nibble
}

void lcd_send_data(uint8_t cmd) {
	// RS = 1 -> data
	LCD_GPIO_BASE ->BSRR = (1 << LCD_PIN_RS);			// Set RS
	lcd_send_4bits(cmd >> 4);							// Send high nibble
	lcd_send_4bits(cmd & 0x0F);							// Send low nibble
}

static void lcd_send_4bits(uint8_t data) {
	//Mask for deleting the old bits
	uint16_t mask = (1 << LCD_PIN_D4) | (1 << LCD_PIN_D5) |
					(1 << LCD_PIN_D6) | (1 << LCD_PIN_D7);
	LCD_GPIO_BASE->BSRR = (mask << 16);						// Set all D4-D7 on low

	// Set individual data bits depending on the value
	if(data & 0x01)	LCD_GPIO_BASE->BSRR = (1 << LCD_PIN_D4);
	if(data & 0x02)	LCD_GPIO_BASE->BSRR = (1 << LCD_PIN_D5);
	if(data & 0x04)	LCD_GPIO_BASE->BSRR = (1 << LCD_PIN_D6);
	if(data & 0x08)	LCD_GPIO_BASE->BSRR = (1 << LCD_PIN_D7);

	lcd_enable_pulse();	// Read pulse
}

static void lcd_enable_pulse(void) {
	LCD_GPIO_BASE->BSRR = (1 << LCD_PIN_E);			//Set E (HIGH)
	delay(200);										// Short wait
	LCD_GPIO_BASE->BSRR = (1 << (LCD_PIN_E + 16));	// Clear E (LOW)
	delay(4000);										// Waiting time after pulse
}

static void delay(uint32_t time) {
	while(time--); //Busy-Wait Delay (not exact, but sufficient fpr simple purposes)
}

