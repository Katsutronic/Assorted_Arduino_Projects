//

int ledPin = 12;
int doublecounter = 0;
int randOn = 0;

void setup(){
  randomSeed(analogRead(0));
//  pinMode(ledPin,OUTPUT);
}

void lightOn(){
  for(int fadeValue = 0; fadeValue <= 255; fadeValue += 15){
    fadeValue = fadeValue > 255 ? 255 : fadeValue;
    analogWrite(ledPin, fadeValue);
    delay(10);
  }
}
void lightOff(){
  for(int fadeValue = 255; fadeValue >= 0; fadeValue -= 15){
    fadeValue = fadeValue < 0 ? 0 : fadeValue;
    analogWrite(ledPin, fadeValue);
    delay(10);
  }
}

void loop(){
  randOn = random(900,3600);
  
  if(doublecounter-- < 0){
     randOn = 150;
     doublecounter = random(2,5);
  }
  //digitalWrite(ledPin,HIGH);
  lightOn();
  delay(randOn);
  //digitalWrite(ledPin,LOW);
  lightOff();
  delay(200);
}


