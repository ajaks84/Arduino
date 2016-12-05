
// Подключаем библиотеки
#include <LiquidCrystal.h>
#include <dht11.h>
// Задаем pin для освещения в спальне
int lineOneIn = 2;
int lineTwoIn = 3;
int lineOneOut = 4;
int lineTwoOut = 5;
// Задаем pin для работы с датчиком DHT
int dHTPin=A0;
int dHTPinPos;
int dHTPinNeg;
// Задаем pin для датчика DHT11
#define DHT11PIN    dHTPin
// Определяем переменные для работы с DHT и дисплеем
LiquidCrystal lcd(9,8,5,4,3,2);
dht11 DHT11;
// Определяем символы для отображения информации крупными цифрами
byte skull_and_bones[8] ={B01110,B10101,B11011,B01110,B00000,B10001,B01110,B10001,};
byte one[8]={B11111,B11111,B11111,B00000,B00000,B00000,B00000,B00000,};
byte two[8]={B00000,B00000,B00000,B00000,B00000,B11111,B11111,B11111,};
byte three[8]={B11111,B11111,B11111,B00000,B00000,B00000,B11111,B11111,};
byte four[8]={B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111,};
byte zero[8]={B00000,B00000,B00000,B00000,B01110,B01110,B01110,B00000,};
byte dots[8]={B00000,B00000,B00011,B00011,B00011,B00011,B00011,B00000,};
byte space[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000,};
byte celsius[8]={B11111,B10001,B10001,B11111,B00000,B00000,B00000,B00000,};
byte rav1[8]={B00000,B00000,B00000,B00000,B00000,B00000,B11111,B11111,};
byte rav2[8]={B11111,B11111,B00000,B00000,B00000,B00000,B00000,B00000,};


void setup()
 {
  pinMode(lineOneIn, INPUT);
  pinMode(lineTwoIn, INPUT);
  pinMode(lineOneOut, OUTPUT);
  pinMode(lineTwoOut, OUTPUT);
  
  lcd.createChar(0,zero);
  lcd.createChar(1,one);
  lcd.createChar(2,two);
  lcd.createChar(3,three);
  lcd.createChar(4,four);
  lcd.createChar(5,celsius);
  lcd.createChar(6,rav1);
  lcd.createChar(7,rav2);
  lcd.begin(16, 2);
 }
void loop()
 {
   
  Serial.begin(9600);
  Serial.print(DHT11.humidity);   
  // Управление освещение в спальне
  bedroomLight();
  delay(1000);
 
         
  }
  
  void bedroomLight ()
  {
   if (digitalRead(lineOneIn) == HIGH){
   digitalWrite (lineOneOut,LOW);
   Serial.print("Line one on");
   }else 
        {digitalWrite (lineOneOut,HIGH);
         Serial.print("Line one off");
         }
         
  { if (digitalRead(lineTwoIn) == HIGH){
   digitalWrite (lineTwoOut,LOW);
   Serial.print("Line two on");
   }else 
        {digitalWrite (lineTwoOut,HIGH);
        Serial.print("Line two off");
         }  }
  }
  
  // Функция вывода на экран крупных символов
void big_digital(int pos,int digit) {
   lcd.setCursor(pos,0);
   switch (digit) {
     case 0:
     lcd.print("\4\1\4");break;
     case 1:
     lcd.print("\1\4 "); break;
     case 2:
     case 3:
     lcd.print("\3\3\4");break;
     case 4:
     lcd.print("\4\2\4");break;
     case 5:
     case 6:
     lcd.print("\4\3\3");break;
     case 7:
     lcd.print("\1\1\4");break;
     case 8:
     case 9:
     lcd.print("\4\3\4"); break;
     case 10:
     lcd.print("\2\4\2"); break;
     case 11:
     lcd.print("\4\2\4");   
     
   }
   lcd.setCursor(pos,1);
   switch (digit) {
     case 0:
     case 8:
     case 6:
     lcd.print("\4\2\4"); break;
     case 1:
     lcd.print("\2\4\2"); break;
     case 2:
     lcd.print("\4\2\2");break;
     case 3:
     case 5:
     case 9:
     lcd.print("\2\2\4"); break;
     case 4:
     lcd.print("  \4"); break;
     case 7:
     lcd.print(" \4 "); break;
     case 10:                          
     lcd.print(" \4\2");break;
     case 11:
     lcd.print("\4 \4"); 
      
     }}
     
  void show_temp(){
  big_digital(2,10);
  lcd.setCursor(6,0);
  lcd.write(6);
  lcd.setCursor(6,1);
  lcd.write(7);
  DHT11.read(DHT11PIN); 
  int t = DHT11.temperature;
  set_position(t);
  lcd.setCursor(15,0);  
  lcd.write(5);         // Знак градуса Цельсия

}

void show_humi(){
big_digital(2,11); 
lcd.setCursor(6,1);
lcd.write(7);
lcd.setCursor(6,0);
lcd.write(6);
DHT11.read(DHT11PIN); 
int t = DHT11.humidity;
set_position(t);
}

// Функция установки позиции курсора для отображения больших цифр.
void set_position(int t){
  if (t < 10) {
  big_digital(12,t);
}
else if (t>=10&t<20){
  big_digital(8,1);
  big_digital(12,t-10);
}
else if (t>=20&t<30){
  big_digital(8,2);
  big_digital(12,t-20);
}
else if (t>=30&t<40){
  big_digital(8,3);
  big_digital(12,t-30);
}
else if (t>=40&t<50){
  big_digital(8,4);
  big_digital(12,t-40);
}}
  
  
