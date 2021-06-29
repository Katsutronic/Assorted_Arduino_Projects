
//Display function

const uint8_t *getNum(int num){
  /*
  switch(num){
    case 0:      return digit_0;
    case 1:      return digit_1;
    case 2:      return digit_2;
    case 3:      return digit_3;
    case 4:      return digit_4;
    case 5:      return digit_5;
    case 6:      return digit_6;
    case 7:      return digit_7;
    case 8:      return digit_8;
    case 9:      return digit_9;
    default:     return digit_0;
  };*/
}

void do_display(int heading){
  char buf[10];
  int originX = display2.width()/2, originY = 15;
  int mode = get_fireMode();
  float heading_rads = (360 - heading) * PI / 180; // 360- because of inverted data
  float offset_r = 0.34906585;

  /*{//The Compass  
    display2.clearDisplay();
  
    display2.drawCircle(originX,originY,6,WHITE);
    display2.drawCircle(originX,originY,7,WHITE);
  
    display2.drawLine(originX,originY,
      originX + (cos(heading_rads + offset_r) * 8),
      originY + (sin(heading_rads + offset_r) * 8),
      WHITE);
    display2.drawLine(originX,originY,
      originX + (cos(heading_rads - offset_r) * 8),
      originY + (sin(heading_rads - offset_r) * 8),
      WHITE);
  
    display2.drawLine(
      originX + (cos(heading_rads + offset_r) * 8),
      originY + (sin(heading_rads + offset_r) * 8),
      originX + (cos(heading_rads) * (12)),
      originY + (sin(heading_rads) * (12)),
      WHITE);
    display2.drawLine(
      originX + (cos(heading_rads - 0.261799) * 8),
      originY + (sin(heading_rads - 0.261799) * 8),
      originX + (cos(heading_rads) * (12)),
      originY + (sin(heading_rads) * (12)),
      WHITE);
    display2.display();
  }*/
  
  if(displayType == 1){//For horizontal display (<3sr and UNSC)
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(8,display.height()/2 + 2);
  /*
    if(mode == modeSemi)
      display.drawBitmap(6,display.height()/2, ardisplay_bullet, 16,8, WHITE);
    else if(mode == modeFull)
      display.drawBitmap(6,display.height()/2, ardisplay_auto, 16,24, WHITE);
    else
      display.println("S");
    */
    display.setTextSize(fontSize);
    display.setCursor(25,display.height()*.2);
    sprintf(buf,"%02d",ammo);
    display.println(buf);
  
    display.drawBitmap(display.width() - 17,display.height()/2 - 6, ardisplay_symbol, 16,24, WHITE);
    display.drawBitmap(1,display.height()/2 - 6, ardisplay_thingy, 24,24, WHITE);
    display.display();
  }
  else if(displayType == 2){//For vertical display (ID and noble logo){
    display.clearDisplay();
    
    display.setTextSize(1);
    display.setCursor(0,display.height()*.75 + 2);
  
    if(mode == modeSemi)
      display.println("1");
    else if(mode == modeFull)
      display.println("A");
    else
      display.println("S");
      
    //Ammo count
    display.setTextSize(fontSize);
    display.setCursor(0,display.height()*.2);
    sprintf(buf,"%02d",ammo); 
    display.println(buf);
    
    display.drawBitmap(0,display.height()*.2,getNum(ammo /10),32,64,WHITE);
    display.drawBitmap(display.width()/2,display.height()*.2,getNum(ammo %10),32,64,WHITE);
    display.drawBitmap(0,display.height()*.75, ardisplay_id,64,32, WHITE);
    display.display();
  }
}

//Returns the position of the fire selector
int get_fireMode(){

  return modeFull;//until I fix the selector
  
/*  if(digitalRead(fireselectPinA) == HIGH)//single shot or safety
    return modeSafe;
  if(digitalRead(fireselectPinB) == HIGH)//semi
    return modeSemi;
  if(digitalRead(fireselectPinC) == HIGH)//full
    return modeFull;
  return modeBad;*/
}

//Handles the firing and reloading buttons
void do_fire(){
  int mode = get_fireMode();
  
  if(digitalRead(triggerPin) == LOW)//unpressed
    triggerTimer = 0;
  else{//pressed
    if(mode == modeFull){
      triggerTimer++;
      if(triggerTimer > fireRate && ammo > 0){
        triggerTimer = 0;
        ammo--;
      }
    }
    else if(mode == modeSemi){
      if(triggerTimer == 0 && ammo > 0){
        triggerTimer++;
        ammo--;
      }
    }
    else{
      ;//nothing
    }
  }
  if(digitalRead(reloadPin) == LOW){//mag out
    reloading = true;
    if(ammo > 0)
      ammo = 1;
    else
      ammo = 0;
  }
  else{//mag in
    if(reloading == true){
      ammo = 60;
      reloading = false;
    }
  }
}

//This evens out the sensor data to reduce jumpiness by averaging the last ten readings
void normalize(int heading){
  normal = 0;
  
  for(int i = 0; i < maxNormal - 1; i++){
    normal_arr[i] = normal_arr[i + 1];
    normal += normal_arr[i];
  }
  
  normal_arr[maxNormal - 1] = heading;
  normal += heading;
  normal /= maxNormal;
}

// Output the data down the serial port.
void Output(int heading){
  Serial.print("Heading: ");
  Serial.print(heading);
  Serial.print("  Ammo: ");
  Serial.print(ammo);
  Serial.print(" Buttons: Trigger: ");
  Serial.print(digitalRead(triggerPin));
  Serial.print(" Reload: ");
  Serial.print(digitalRead(reloadPin));
  Serial.print(" Selector: ");
  Serial.println("");
}

