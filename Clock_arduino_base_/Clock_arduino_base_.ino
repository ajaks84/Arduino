boolean sets = false;
int cur_millis , lastTick, setTick = 0; 
int sec, mins, hour = 0; 
int b1, b2 = 0;
 
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,9,6,5,4);
 #define GNDPIN      28
void setup() {
lcd.begin(16, 2);
pinMode(8, INPUT);
pinMode(7, INPUT);
sets = true;
}
 
void loop() {
  cur_millis  = millis(); //time
 
  if (cur_millis - lastTick >= 1000) {
    lastTick = cur_millis;
    sec++;
    if (sec >= 60) {
    mins++;
    sec = 0; 
 
  }
 
  if (mins >=60) {
    hour++;
    mins = 0; 
  }
 
  if (hour >=24) {
    hour=0;
    mins = 0; 
  }
  lcd.setCursor(0,0);
  lcd.print("Clock");
  lcd.setCursor(1,1);
 
if (hour < 10) {lcd.print("0");}
  lcd.print(hour);
  lcd.print(":");
if (mins < 10) {lcd.print("0");}
  lcd.print(mins);
  lcd.print(":");
if (sec < 10) {lcd.print("0");}
  lcd.print(sec);
  }
check_sets();
myFunc();
}
 
void check_sets() { 
  if (sets) { 
  if (cur_millis - setTick >= 300) {
       sets = false;
       setTick = 0;
    } 
  } else {
   b1 = digitalRead(7); 
   if (b1 == HIGH) {
      hour++; sec=0; sets = true; setTick = cur_millis;
    }
   b2 = digitalRead(8);
   if (b2 == HIGH) {
      mins++; sec=0; sets = true; setTick = cur_millis;
    }

}



}

void myFunc(){
 if (sec>20){
 digitalWrite(22, HIGH); 
 //digitalWrite(22, GND); 
 
 }
 
 else digitalWrite(22, LOW); 
}
