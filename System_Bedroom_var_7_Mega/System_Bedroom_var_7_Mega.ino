#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <SoftwareSerial.h>   // Модуль для работы с Serial

#define dht_br 2
#define dht_chr 3
#define dht_hr 6

dht DHT;

//int incomingByte = 0;         // Переменная для хранения входных данных

//SoftwareSerial BTSerial(19, 18); // Пины для RX, TX 

float t=0;
float h=0;
float t1=0;
float h1=0;
float t2=0;
float h2=0;

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

LiquidCrystal_I2C lcd(0x27,16,2); //27
LiquidCrystal_I2C lcd_1(0x23,16,2);
LiquidCrystal_I2C lcd_2(0x26,16,2); //26



tmElements_t tm;

void setup() {
  
  

  //BTSerial.begin(9600);           

  pinMode(4, INPUT); 
  pinMode(5, OUTPUT);  
  pinMode(6, OUTPUT); 
  pinMode(22, OUTPUT);


  lcdInit(0);
  lcd.init();
        lcd.backlight();
  lcdInit(1); 
  lcdInit(2);

  bool parse=false;
  bool config=false;


 /* if(digitalRead(4)==HIGH){
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
  } 
   if (parse) {
    lcd.setCursor(0, 0);
    lcd.println("Communic. Error");
    lcd.setCursor(0, 1);
    lcd.println("Check circuit");
  } 
  
  delay(700);
  lcd.clear();
*/}

void loop() {

  boolean manSt=true;

  /*if(BTSerial.available()>0)       // Если имеются в порту данные
  {
    incomingByte = BTSerial.read();    // считывание данных
    if(incomingByte!=-1)              // если данные не равны -1
    { 

      if(incomingByte==49){
        lcdInit();
  
         
      }

      if(incomingByte==50){
        lcd1Init(); 

      }

      BTSerial.print("\nI received: ");     // вывод сообщения
      BTSerial.println(incomingByte, DEC);  // вывод данных
    }
  }*/


  if (tm.Hour<=6 | tm.Hour>=20 ) {
    digitalWrite(5, HIGH);
  } 
  else {
    digitalWrite(5, LOW); 
  }
  
  if(tm.Minute==05 & tm.Second==07){
    
        lcdInit(0);

      }
      
       if(tm.Minute==06 & tm.Second==07){
        
        lcdInit(1); 
        
      }
      
      if(tm.Minute==07 & tm.Second==07){
        
        lcdInit(2);

      }



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
    print2digits_1(tm.Month);
    
    lcd_2.setCursor(0, 0);
    print2digits_2(tm.Hour);
    lcd_2.write(':');
    print2digits_2(tm.Minute);
    lcd_2.write(':');
    print2digits_2(tm.Second);
    lcd_2.setCursor(10, 0);
    lcd_2.print(tm.Day);
    lcd_2.write('/');
    print2digits_2(tm.Month);
  }


 /* else {

    if (RTC.chipPresent()) {
      lcd.setCursor(0, 0);
      lcd.println("DS1307 stopped");
      lcd_1.setCursor(0, 0);
      lcd_1.println("DS1307 stopped");
      lcd_2.setCursor(0, 0);
      lcd_2.println("DS1307 stopped");


    } 
    else {
      lcd.setCursor(0, 0);
      lcd.println("DS1307 rd error!");
      lcd_1.setCursor(0, 0);
      lcd_1.println("DS1307 rd error!");
      lcd_2.setCursor(0, 0);
      lcd_2.println("DS1307 rd error!");

    }

  }*/

  if (tm.Second==05){

    DHT.read22(dht_br);
    t=DHT.temperature-0.3;
    h=DHT.humidity;

  }



  lcd.setCursor(1, 1);
  lcd.write(1);
  lcd.print(t,1);
  lcd.print((char)223); //degree sign
  lcd.setCursor(10, 1);
  lcd.write(2);
  lcd.print(h,0);
  lcd.print("%");

  if (tm.Second==10){

    DHT.read22(dht_chr);
    t1=DHT.temperature-0.3;
    h1=DHT.humidity;

  }

  lcd_1.setCursor(1, 1);
  lcd_1.write(1);
  lcd_1.print(t1,1);
  lcd_1.print((char)223); 
  lcd_1.setCursor(10, 1);
  lcd_1.write(2);
  lcd_1.print(h1,0);
  lcd_1.print("%");
  
  if (tm.Second==15){

    DHT.read22(dht_hr);
    t2=DHT.temperature-0.3;
    h2=DHT.humidity;

  }
  lcd_2.setCursor(1, 1);
  lcd_2.write(1);
  lcd_2.print(t2,1);
  lcd_2.print((char)223); 
  lcd_2.setCursor(10, 1);
  lcd_2.write(2);
  lcd_2.print(h2,0);
  lcd_2.print("%");


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

void print2digits_2(int number) {
  if (number >= 0 && number < 10) {
    lcd_2.write('0');
  }
  lcd_2.print(number);
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


void lcdInit(int i){
  
        if (i=0){
        lcd.clear();
        delay(500);
        lcd.createChar(1,termometru);
        delay(500);
        lcd.createChar(2,picatura);
        delay(500);
        lcd.init();
        lcd.backlight(); 
      }
        if (i=1){
        lcd_1.clear();
        delay(500);
        lcd_1.createChar(1,termometru);
        delay(500);
        lcd_1.createChar(2,picatura);
        delay(500);
        lcd_1.init();
        lcd_1.backlight();
      }
        if (i=2){
        lcd_2.clear();
        delay(500);
        lcd_2.createChar(1,termometru);
        delay(500);
        lcd_2.createChar(2,picatura);
        delay(500);
        lcd_2.init();
        lcd_2.backlight();
      } 
}



