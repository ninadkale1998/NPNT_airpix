/**
 * @ file ppm_readwrite.h
 * @ brief List of ppm read write Variables
 * @ author Ninad Kale
 * @ copyright (c) Airpix-India 2019
 */



#ifndef _PPM_READWRITE_H_
#define _PPM_READWRITE_H_

#include <PPMReader.h>
//#include <InterruptHandler.h>   <-- You may need this on some versions of Arduino

/*********************************** ppm write ************************************************/
#define chanel_number 8  //set the number of chanels
#define default_servo_value 1500  //set the default servo value
#define PPM_FrLen 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 10  //set PPM signal output pin on the arduino
unsigned long  ppm[chanel_number];

/*********************************** ppm write ************************************************/



/*********************************** ppm read ************************************************/

int interruptPin = 3;
PPMReader ppm_obj(interruptPin, chanel_number);

//int interruptPin_ = 2;
//PPMReader ppm_obj1(interruptPin_, chanel_number);

/*********************************** ppm read ************************************************/
#include "PPMfunctions.h"

#endif
