#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_1(0x27,16,2); 
LiquidCrystal_I2C lcd_2(0x23,16,2);

void setup() {
 
  lcd_1.init(); 
  lcd_2.init(); 
  lcd_1.print("I'm cool"); 
  lcd_2.print("I'm cool too"); 
  
}

void loop() {}
