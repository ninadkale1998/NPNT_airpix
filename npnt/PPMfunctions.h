#include "Arduino.h"

/**************************************************************************************************************************/

void Initppm(){
   for(int i=0; i<chanel_number; i++){
      ppm[i]= default_servo_value ;
   }
  
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, !onState);  //set the PPM signal pin to the default state (off)
  
  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;
  
  OCR1A = 100;  // compare match register, change this
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
  
}


/**************************************************************************************************************************/

ISR(TIMER1_COMPA_vect){  //leave this alone
  static boolean state = true;
  
  TCNT1 = 0;
  
  if(state) {  //start pulse
    digitalWrite(sigPin, onState);
    OCR1A = PPM_PulseLen * 2;
    state = false;
  }
  else{  //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;
  
    digitalWrite(sigPin, !onState);
    state = true;

    if(cur_chan_numb >= chanel_number){
      cur_chan_numb = 0;
      calc_rest = calc_rest + PPM_PulseLen;// 
      OCR1A = (PPM_FrLen - calc_rest) * 2;
      calc_rest = 0;
    }
    else{
      OCR1A = (ppm[cur_chan_numb] - PPM_PulseLen) * 2;
      calc_rest = calc_rest + ppm[cur_chan_numb];
      cur_chan_numb++;
    }     
  }
}
/**************************************************************************************************************************/

void ReadPPM(){
          for (int channel = 1; channel <= chanel_number; ++channel) {
        unsigned long value = ppm_obj.latestValidChannelValue(channel, 0);
        Serial.print(String(value) + " ");
    }
    Serial.println();
    }

/**************************************************************************************************************************/
 
void Arm_vehicle(){
  //Serial.println("arm mode");
          for (int channel = 0; channel < chanel_number; channel++) {
        ppm[channel] = ppm_obj.latestValidChannelValue(channel, 0);
        Serial.print(String(ppm[channel]) + " ");
    }
    Serial.println();
    }

/**************************************************************************************************************************/

void RTL_mode(){
  //Serial.println("rtl mode");
  for (int channel = 1; channel <= chanel_number-1; ++channel) {
            ppm[channel] = ppm_obj.latestValidChannelValue(channel, 0); 
       Serial.print(String(ppm[channel]) + " ");
       }
  ppm[chanel_number] = 1250;
  Serial.print(String(ppm[chanel_number]) + " ");     
  // write ppm value
  Serial.println();
  
  }

/**************************************************************************************************************************/

void Wait_mode(){
  //Serial.println("wait mode");
  for (int channel = 1; channel <= chanel_number-2; ++channel) {
            ppm[channel] = default_servo_value; 
       Serial.print(String(ppm[channel]) + " ");
       }
  
  Serial.println();
  }
