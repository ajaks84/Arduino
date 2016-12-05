#include <SoftwareSerial.h>   // Модуль для работы с Serial
 
int incomingByte = 0;         // Переменная для хранения входных данных
 
SoftwareSerial mySerial(0, 1); // Пины для RX, TX 
 
void setup()
{
   mySerial.begin(115200);           // Скорость передачи по Serial
   mySerial.print("I'm working");  
  /*pinMode(4, OUTPUT);  digitalWrite(4, HIGH);  
  pinMode(5, OUTPUT);  digitalWrite(5, HIGH);
  pinMode(6, OUTPUT);  digitalWrite(6, HIGH); 
  pinMode(7, OUTPUT);  digitalWrite(7, HIGH);*/
}
void loop()
{
  if(mySerial.available()>0)       // Если имеются в порту данные
  {
     incomingByte = mySerial.read();    // считывание данных
      if(incomingByte!=-1)              // если данные не равны -1
      {
        if(incomingByte==49){
        mySerial.print("1");
        }
        
        /*if(incomingByte==50){
        digitalWrite(5, LOW); 
        }
        
        if(incomingByte==51){
        digitalWrite(6, LOW); 
        }
        
        if(incomingByte==52){
        digitalWrite(7, LOW); 
        }
        
        if(incomingByte==53){
        digitalWrite(4, HIGH); 
        }
        
        if(incomingByte==54){
        digitalWrite(5, HIGH); 
        }
        
        if(incomingByte==55){
        digitalWrite(6, HIGH); 
        }
        
        if(incomingByte==56){
        digitalWrite(7, HIGH); 
        }*/
        
        
        mySerial.print("\nI received: ");        //вывод сообщения
        mySerial.println(incomingByte, DEC);  // вывод данных
      }
  }
  
  
}
