// Измерение температуры

#include <LiquidCrystal.h>
#include <DHT22.h>
#define DHT22_PIN 8

DHT22 myDHT22(DHT22_PIN);

byte PE_lit[8] =
{
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000,
};

byte EL_lit[8] =
{
  B00111,
  B01001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000,
};

byte ZH_lit[8] =
{
  B10001,
  B10101,
  B10101,
  B01110,
  B10101,
  B10101,
  B10001,
  B00000,
};

byte MZ_lit[8] =
{
  B10000,
  B10000,
  B10000,
  B11110,
  B10001,
  B10001,
  B11110,
  B00000,
};

byte U_lit[8] =
{
  B10001,
  B10001,
  B10001,
  B01111,
  B00001,
  B00001,
  B11110,
  B00000,
};

LiquidCrystal lcd(2,3,4,5,6,7);

void setup()
{
  lcd.createChar(1, PE_lit);
  lcd.createChar(2, U_lit);
  lcd.createChar(3, EL_lit);
  lcd.createChar(4, ZH_lit);
  lcd.createChar(5, MZ_lit);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("TEM\1EPAT\2PA");
  lcd.setCursor(1, 1);
  lcd.print("B\3A\4HOCT\5");
}

void loop()
{

 int chk = myDHT22.readData();

    lcd.setCursor(12, 0);
    lcd.print(myDHT22.getTemperatureC(), 1);
    lcd.setCursor(14, 0);
    lcd.print("");
    //lcd.setCursor(15, 0); for DHT 11
    //lcd.print("C");
    lcd.setCursor(12, 1);
    lcd.print(myDHT22.getHumidity(), 1);
    lcd.setCursor(14, 1);
    lcd.print("");
    //lcd.setCursor(15, 1);
    //lcd.print("%");
    
    delay(2000);
}
