#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_LSM303.h>
#include <Adafruit_Sensor.h>
#include "ar_stuff.h"
#include "ar_bmp.h"

//Compass variables
Adafruit_LSM303_Mag mag = Adafruit_LSM303_Mag(12345);
int error = 0;
int linelength = 15;

//Ammo counter and button variables
int ammo = 60;
int triggerTimer = 0;
int fireRate = 5; //A constant for the rate of fire on the gun
int fontSize = 5;
int fullAuto = 1; //toggle for semi/auto
bool reloading = false;

void setup(){
  Serial.begin(9600);

  {//Magnetometer setup start
    Serial.println("Magnetometer Test"); Serial.println("");
    if(!mag.begin())
    {
      Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
      while(1);
    }
  }//End magnetometer setup

  pinMode(triggerPin, INPUT);
  pinMode(reloadPin, INPUT);
  pinMode(fireselectPinA, INPUT);
  pinMode(fireselectPinB, INPUT);
  pinMode(fireselectPinC, INPUT);

  {//Display Setup
    display.begin(SSD1306_SWITCHCAPVCC);
    display.display(); // show splashscreen
    delay(2000);
    display.clearDisplay();   // clears the screen and buffer
//  display.drawBitmap(0, 0,  ardisplay_TEST, 128, 64, 1);
//  display.display();
    display.setRotation(3);
    display.setTextColor(WHITE);
    display.setTextSize(fontSize);
  delay(2000);
  }//End Display setup
}

void loop(){
  float heading = 0.0;
  int digit1 = ammo % 10, digit2 = ammo / 10;
    
  {//Magnetometer stuff
    /* Get a new sensor event */ 
    sensors_event_t event; 
    mag.getEvent(&event);
    
    // Calculate the angle of the vector y,x
    heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / PI;
    
    // Normalize to 0-360
//    if (heading < 0){
  //    heading = 360 + heading;
    //}
    Output(event.magnetic.x,event.magnetic.y,heading,heading);
  }//End magnetometer
  
  //Display stuff
  do_display(heading);
  
  //Ammo counter, for now just counts down.
  do_fire();
}

