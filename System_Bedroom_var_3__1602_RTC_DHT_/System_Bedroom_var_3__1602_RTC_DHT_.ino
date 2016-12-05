#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h>
#include <DHT22.h>

#define DHT22_PIN 2

DHT22 myDHT22(DHT22_PIN);

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

LiquidCrystal_I2C lcd(0x23,16,2); 

tmElements_t tm;

void setup() {
  
  lcd.createChar(1,termometru);
  lcd.createChar(2,picatura);
  lcd.init();                      
  
  bool parse=false;
  bool config=false;

  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

  //Serial.begin(9600);
  //while (!Serial) ; // wait for Arduino Serial Monitor
  //delay(200);
  if (parse && config) {
    lcd.setCursor(0, 0);
    lcd.print("Time configured");
  } else if (parse) {
    lcd.setCursor(0, 0);
    lcd.println("Communication Error");
    lcd.setCursor(0, 1);
    lcd.println("Check circuitry");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Could not parse info");
  }
  delay(1000);
  lcd.clear();
}

void loop() {
  
  int chk = myDHT22.readData();
  tmElements_t tm;
  
  if (tm.Hour>=7) {lcd.backlight();}
  else {lcd.noBacklight(); }
  

  if (RTC.read(tm)) {
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
    //lcd.write('/');
    //lcd.print(tmYearToCalendar(tm.Year));
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.print(myDHT22.getTemperatureC(), 1);
    lcd.print((char)223); //degree sign
    //Serial.print(myDHT22.getTemperatureC(), 1);
    lcd.setCursor(9, 1);
    lcd.write(2);
    lcd.print(myDHT22.getHumidity(), 1);
    lcd.print("%");
    //Serial.print(myDHT22.getHumidity(), 1);
   
    
  } else {
    if (RTC.chipPresent()) {
      lcd.setCursor(0, 0);
      lcd.println("DS1307 stopped");
      delay(5000);
      lcd.clear();
    } else {
      lcd.setCursor(0, 0);
      lcd.println("DS1307 rd error!");
      delay(5000);
      lcd.clear();
    }
    delay(9000);
  }
  delay(1000);
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

