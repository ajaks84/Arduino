/*
  # Example code for the moisture sensor
  # Editor     : Lauren
  # Date       : 13.01.2012
  # Version    : 1.0
  # Connect the sensor to the A0(Analog 0) pin on the Arduino board
   
  # the sensor value description
  # 0  ~300     dry soil
  # 300~700     humid soil
  # 700~950     in water
*/
 
void setup(){
  
  Serial.begin(9600);
   
}
 
void loop(){
  
  
  Serial.println(analogRead(0));
  
  delay(1000);
  
 
}
