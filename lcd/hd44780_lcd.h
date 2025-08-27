/*
 * hd44780_lcd.h
 *
 *  Created on: Aug 27, 2025
 *      Author: Benoit Christian Mbole Zogo
 */

#ifndef HD44780_LCD_H_
#define HD44780_LCD_H_

#include <stdint.h>

//user config: change GPIO port and pins as needed
#define	LCD_GPIO_BASE		GPIOD					// GPIO-Port for the LCD
#define LCD_GPIO_ENR		RCC_AHB1ENR_GPIODEN		// Clock enable for GPIOD
#define LCD_RCC_ENR_REG		RCC ->AHB1ENR			// Register for clock enable

// Pins assignment for LCD control
#define LCD_PIN_RS			(0)		//Register Select (command/data)
#define LCD_PIN_E			(1)		// Enable signal
#define LCD_PIN_D4			(2)		// Data line D4
#define LCD_PIN_D5			(3)		// Data line D5
#define LCD_PIN_D6			(4)		// Data line D6
#define LCD_PIN_D7			(5)		// Data line D7

void lcd_init(void);							// Initialise LCD
void lcd_clear(void);							// Clear LCD
void lcd_put_cur(uint8_t row, uint8_t col);		// Position cursor
void lcd_send_string(char *str);				// Send string to LCD
void lcd_send_data(uint8_t data);				// Send single data byte
void lcd_send_cmd(uint8_t cmd);					// Send command


#endif /* HD44780_LCD_H_ */
