int analogPin = A0;     // номер порта к которому подключен потенциометр
int val = 0;           // переменная для хранения считываемого значения
 
void setup()
{
  pinMode(2, INPUT);
  Serial.begin(9600);              //  установка связи по serial
}
 
void loop()
{
  val = analogRead(analogPin);  // считываем значение
  delay(1000);
  Serial.println(val);
  if (val>990) {
    
    delay(1000);
    //digitalWrite(2,HIGH);
    //Serial.println(val);
    
  
  }else if (val<400) {delay(1000);
                      //digitalWrite(2,LOW);
                    }           
}

