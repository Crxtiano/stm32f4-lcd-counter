# STM32 LCD 1602A – Scrolling Text Demo

This project demonstrates how to control an **HD44780-compatible LCD (16x2)** with an **STM32F4** in **4-bit mode**.  
It shows two ways of displaying long texts:
1. **Page Scroll** – jumps in blocks of 32 characters (2 lines × 16 characters).
2. **Smooth Scroll** – smooth scrolling text across both lines.

---

## 🔧 Hardware
- Microcontroller: **STM32F407G-DISC1** (or compatible)
- Display: **LCD 1602A (HD44780 compatible)**
- Control: **4-bit mode**

### Pin assignment (example)
| LCD pin | STM32 pin (port D) |
|---------|---------------------|
| RS      | PD0 |
| E       | PD1 |
| D4      | PD2 |
| D5      | PD3 |
| D6      | PD4 |
| D7      | PD5 |

*(Can be adjusted depending on setup → see `hd44780_lcd.h`)*

---

## 📂 Code overview
### LCD driver (`lcd/hd44780_lcd.c`)
- `lcd_init()` – Initialise the LCD in 4-bit mode
- `lcd_clear()` – Clear display
- `lcd_put_cur(row, col)` – Set cursor
- `lcd_send_cmd(cmd)` – Send command
- `lcd_send_data(data)` – Send character
- `lcd_send_string(str)` – Output string

### Scrolling functions (`Core/Src/main.c`)
- **Page Scroll**: `lcd_show_page(char* text, int page)`
- **Smooth Scroll**: `lcd_show_window(char* text, int offset)`

---

## ▶️ Example
### Page Scroll
```c
char* message = ‘This is a long message for the LCD 1602A...’;
int len = strlen(message);
int total_pages = (len + 31) / 32;
while(1) {
    for(int page=0; page<total_pages; page++) {
        lcd_show_page(message, page);
        delay_ms(2000);
    }
}
