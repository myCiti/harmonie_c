#include <LiquidCrystal_I2c.h>
LiquidCrystal_I2C lcd(0x27,20,4);

void lcd_print(const char* msg, int row, int col){
    lcd.setCursor(col-1, row-1);
    lcd.print(msg);
}