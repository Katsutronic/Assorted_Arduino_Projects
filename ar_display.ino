#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306_32.h>
#include <Adafruit_SSD1306_64.h>
#include <LSM303.h>
#include "ar_stuff.h"
#include "ar_bmp.h"

//Compass variables
LSM303 compass;
int cmp_minx = 98;
int cmp_miny = -958;
int cmp_minz = -487;
int cmp_maxx = 1119;
int cmp_maxy = 59;
int cmp_maxz = 418;

int error = 0;
int linelength = 15;

const int maxNormal = 10;
int normal = 0;
int normal_arr[maxNormal];

int displayType = 1;

//Ammo counter and button variables
int ammo = 60;
int triggerTimer = 0;
int fireRate = 2; //A constant for the rate of fire on the gun
int fontSize = 1;
bool reloading = false;


/*
  Main functions start here
*/

void setup(){
  Serial.begin(9600);
  Wire.begin();
  
  {//Magnetometer setup start
    compass.init();
    compass.enableDefault();
    compass.m_min.x = cmp_minx;
    compass.m_min.y = cmp_miny;
    compass.m_min.z = cmp_minz;
    
    compass.m_max.x = cmp_maxx;
    compass.m_max.y = cmp_maxy;
    compass.m_max.z = cmp_maxz;
  }//End magnetometer setup

  {//Pin Setup
    pinMode(triggerPin, INPUT);
    pinMode(reloadPin, INPUT);
/*    pinMode(fireselectPinA, INPUT);
    pinMode(fireselectPinB, INPUT);
    pinMode(fireselectPinC, INPUT);*/
    pinMode(ledPin, OUTPUT);
  }
  {//Display Setup
    display.begin(SSD1306_SWITCHCAPVCC);
    display2.begin(SSD1306_SWITCHCAPVCC);

    display.display(); // show splashscreen
    display2.display();

    delay(1000);
    
    display.clearDisplay();   // clears the screen and buffer
    display2.clearDisplay();   // clears the screen and buffer
//  display.drawBitmap(0, 0,  ardisplay_TEST, 128, 64, 1);
//  display.display();

    if(displayType == 1){
      display.setRotation(0);
      fontSize = 2;
    }
    else if(displayType == 2){
      display.setRotation(1);
      fontSize = 5;
    }
    display.setTextColor(WHITE);
    display.setTextSize(fontSize);
    
    display2.setTextColor(WHITE);
    display2.setTextSize(fontSize);
    delay(1000);
  }//End Display setup
  digitalWrite(ledPin,HIGH);
}

void loop(){
  compass.read();
  int heading = compass.heading((LSM303::vector){0,-1,0});
  int digit1 = ammo % 10, digit2 = ammo / 10;

  {//Magnetometer stuff
    //Normalize the output via a fun array
    normalize(heading);

    Output(normal);
  }//End magnetometer

  //Display stuff
  do_display(heading);

  //Ammo counter, for now just counts down.
  do_fire();
}

