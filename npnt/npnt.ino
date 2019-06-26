/**
 * @ file NPNT module
 * @ author Ninad Kale
 * @ copyright (c) Airpix-India 2019
 */


#include "PPM_readwrite.h"
#include "GPRSHeader.h"

void setup() {
  SIM900.begin(9600);  /* Define baud rate for software serial communication */
  Serial.begin(9600);
  Initgprs();
  Initppm();
  loop_prevtime = millis();
  prevtime = millis();  
}

void loop() {
  loop_timer = millis() - loop_prevtime;

  if(!arm && !rtl){
    Ping_server();
    loop_prevtime = millis();
    }
  else if(loop_timer > 1000){
    //Serial.println("checking server");
    Ping_server();
    loop_prevtime = millis();
    }
    
  else if(loop_timer%100 == 0){
     if(rtl){
      RTL_mode();  
     }
     else if(arm){
      Arm_vehicle();
     }
     else{
      Wait_mode();
     }
     //loop_prevtime = millis();
  
/*
//////////////////////////////////////////////////////////// ppm read ///////////////////////////////////////////////////////////////////////// 
    Serial.print("...................");
    for (int channel = 1; channel <= 8; ++channel) {
        unsigned long value = ppm_obj1.latestValidChannelValue(channel, 0);
        Serial.print(String(value) + " ");
    }
     Serial.print("...................");
    Serial.println();
    
//////////////////////////////////////////////////////////// ppm read /////////////////////////////////////////////////////////////////////////    
*/  }

  
}
