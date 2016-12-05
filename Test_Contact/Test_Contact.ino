void setup()     
 { 
      Serial.begin(9600);  
      pinMode(4, INPUT);                
 } 

 void loop() 

 { 
      if(digitalRead(4)==HIGH)
      { 
      Serial.println("Push");
      delay(1000);
      } 
      else 
      { 
       Serial.println("noPush");
       delay(1000);
      } 

          
 } 
