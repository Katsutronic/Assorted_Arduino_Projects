const int ledMax = 4;
int ledPins[ledMax] = {9,10,14,15};


void setup(){
  randomSeed(analogRead(0));
  
  for(int i = 0; i < ledMax; i++)
    pinMode(ledPins[i],OUTPUT);
}

void loop(){
  for(int i = 0; i < ledMax; i++)
    analogWrite(ledPins[i],random(255));
  
  delay(100);
}

