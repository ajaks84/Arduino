#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Time.h>   
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
 
 
const int buttonPin = 5;
const int LowLight = 9; 
const int RedLight = 11;   
const int GreenLight = 10; 
const int DrySoil = 12;
const int Relay_1 = 22;

LiquidCrystal_I2C lcd(0x27,16,2); 



int SoilState = 0;
int val = 0; 
int counter = 0;
int currentState = 0;
int previousState = 0;
 
 
void setup(){
  pinMode(RedLight, OUTPUT);  
  pinMode(GreenLight, OUTPUT); 
  pinMode(DrySoil, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(LowLight, INPUT);
  pinMode(Relay_1, OUTPUT);
  
  setTime(13,50,0,15,07,2014);
  
  lcdInit();
                   
}

void lcdInit(){
lcd.init();                        
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  
}
 
void loop(){
  
  counterSet();
if (counter == 3){counter=0;};
  
 if (counter==0){ 
 lcd.clear();
 
 show_humi();}
 
 if (counter==1){ 
 lcd.clear();
 show_time();}
 
 if (counter==2){ 
 lcd.clear();
 show_light();
 }
 
 soilState ();
  
  }
  
  void soilState (){
    
  SoilState = digitalRead(DrySoil);
  
  if(SoilState== LOW){
  digitalWrite(RedLight, HIGH);
  digitalWrite(GreenLight, LOW);
  }
 
  if(SoilState== HIGH){
  digitalWrite(RedLight, LOW);
  digitalWrite(GreenLight, HIGH);
  delay(300);
  digitalWrite(GreenLight, LOW);
  delay(300);
  }
  
  //if (LowLight== HIGH){digitalWrite(Relay_1, HIGH);}
  //if (LowLight== LOW){digitalWrite(Relay_1, LOW);}
  if (analogRead(1)> 500){digitalWrite(Relay_1, 1);}
   if (analogRead(1)< 500){digitalWrite(Relay_1, 0);}
  
  }
  
void show_light(){
lcd.setCursor(0, 0);
lcd.print("Lightness is:");
lcd.setCursor(6, 1);          
lcd.print(analogRead(1));
  }
  
void counterSet(){  
  val = digitalRead(buttonPin);
  
  if (val == HIGH) { 
      currentState = 1;
      }
else {
currentState = 0;
}
if(currentState != previousState){
if(currentState == 1){
counter = counter + 1;

}
}
previousState = currentState;
delay(500);  

}


void show_humi(){
lcd.setCursor(0, 0);
lcd.print("Soil Humidity is:");
lcd.setCursor(6, 1);          
lcd.print(analogRead(0));
}

void show_time(){                      
lcd.setCursor(2, 0);              
printDigit(day());
lcd.setCursor(4, 0);              
lcd.print("-");
lcd.setCursor(5, 0); 
printDigit(month());
lcd.setCursor(7, 0);              
lcd.print("-");
lcd.setCursor(8, 0);              
lcd.print(year());
lcd.setCursor(3, 1);
printDigit(hour());
lcd.setCursor(5, 1);
printDigits(minute());
lcd.setCursor(8, 1);
printDigits(second());
}

void printDigits(int digits){
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
void printDigit(int digits){
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
 
 

