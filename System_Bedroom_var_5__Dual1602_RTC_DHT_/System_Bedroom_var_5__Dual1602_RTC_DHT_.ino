#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <SoftwareSerial.h>   // Модуль для работы с Serial

#define dht_br 2
#define dht_chr 3

dht DHT;

int incomingByte = 0;         // Переменная для хранения входных данных

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

byte termometru[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte picatura[8] = //icon for water droplet
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};

LiquidCrystal_I2C lcd(0x27,16,2); 
LiquidCrystal_I2C lcd_1(0x23,16,2);

tmElements_t tm;

void setup() {
  
  pinMode(4, INPUT);
  
  lcd.createChar(1,termometru);
  lcd.createChar(2,picatura);
  lcd.init(); 
  lcd_1.createChar(1,termometru);
  lcd_1.createChar(2,picatura);
  lcd_1.init();  
  
  bool parse=false;
  bool config=false;
  
if(digitalRead(4)==HIGH){
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    
    if (RTC.write(tm)) {
      config = true;
    }
  }
}

  if (parse && config) {
    lcd.setCursor(0, 0);
    lcd.print("Time configured");
  } else if (parse) {
    lcd.setCursor(0, 0);
    lcd.println("Communic. Error");
    lcd.setCursor(0, 1);
    lcd.println("Check circuit");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Push bt to parse");
  }
  delay(2000);
  lcd.clear();
}

void loop() {

  //tmElements_t tm;
  
  if (tm.Hour>=7) {lcd.backlight(); lcd_1.backlight(); }
  else {lcd.noBacklight(); lcd_1.noBacklight();}
  
  if (tm.Second==01){lcd.clear(); lcd_1.clear();}
    
    
    if(RTC.read(tm)){ 
    
    lcd.setCursor(0, 0);
    print2digits(tm.Hour);
    lcd.write(':');
    print2digits(tm.Minute);
    lcd.write(':');
    print2digits(tm.Second);
    lcd.setCursor(10, 0);
    lcd.print(tm.Day);
    lcd.write('/');
    print2digits(tm.Month);
    
    lcd_1.setCursor(0, 0);
    print2digits_1(tm.Hour);
    lcd_1.write(':');
    print2digits_1(tm.Minute);
    lcd_1.write(':');
    print2digits_1(tm.Second);
    lcd_1.setCursor(10, 0);
    lcd_1.print(tm.Day);
    lcd_1.write('/');
    print2digits_1(tm.Month);}
    
    
    else {
      
      if (RTC.chipPresent()) {
      lcd.setCursor(0, 0);
      lcd.println("DS1307 stopped");
      lcd_1.setCursor(0, 0);
      lcd_1.println("DS1307 stopped");
      
      
    } else {
      lcd.setCursor(0, 0);
      lcd.println("DS1307 rd error!");
      lcd_1.setCursor(0, 0);
      lcd_1.println("DS1307 rd error!");
      
    }
    
    }
    
    DHT.read22(dht_br);
    
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.print(DHT.temperature-0.3,1);
    //lcd.print("lcd");
    lcd.print((char)223); //degree sign
    lcd.setCursor(10, 1);
    lcd.write(2);
    lcd.print(DHT.humidity,0);
    lcd.print("%");
    
    //DHT.read22(dht_chr);
    
    lcd_1.setCursor(1, 1);
    lcd_1.write(1);
    delay(1000);
    DHT.read22(dht_chr);
    lcd_1.print(DHT.temperature-0.3,1);
    //lcd_1.print("lcd_1");
    lcd_1.print((char)223); 
    lcd_1.setCursor(10, 1);
    lcd_1.write(2);
    lcd_1.print(DHT.humidity,0);
    lcd_1.print("%");
   
    
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
 lcd.print(number);
}

void print2digits_1(int number) {
  if (number >= 0 && number < 10) {
    lcd_1.write('0');
  }
 lcd_1.print(number);
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

