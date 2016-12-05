const int buttonPin = 6;   
const int ledPin =  13; 
const int lightPin = 7;

int buttonState = 0;   
int ledState = 0;

void setup() {
  
  pinMode(ledPin, OUTPUT);    
  pinMode(10, OUTPUT);    
  pinMode(11, OUTPUT);     
  
  pinMode(buttonPin, INPUT);
  pinMode(lightPin, INPUT);  
}

void loop(){
  
   ledState = digitalRead(lightPin);
   buttonState = digitalRead(buttonPin);
   
  if (ledState == HIGH) {      

   digitalWrite(10, HIGH);
   digitalWrite(ledPin, HIGH); 
   delay(300);
  
  } 
  else {
    digitalWrite(ledPin, LOW); 
    digitalWrite(10, LOW); 
    
  }
  if (buttonState == HIGH) {        
    digitalWrite(ledPin, HIGH); 
  digitalWrite(11, HIGH); 
  delay(200);
  } 
  else {
    digitalWrite(ledPin, LOW); 
    digitalWrite(11, LOW); 
   
  }
}
