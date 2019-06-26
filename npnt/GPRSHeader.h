/**
 * @ file GPRSHeader.h
 * @ brief List of gprs Variables
 * @ author Ninad Kale
 * @ copyright (c) Airpix-India 2019
 */



#ifndef _GPRS_Header_H_
#define _GPRS_Header_H_

/**************************************************************************************************************************/


#include <SoftwareSerial.h>    /* Create object named SIM900 of the class SoftwareSerial */

int txd_pin = 8;
int rxd_pin = 7;
SoftwareSerial SIM900(txd_pin, rxd_pin);

int index_of_rtl;
int index_of_arm; 

bool arm = false;
bool rtl = false;
bool httpread = false;
String data1,data;
int case_no = 0;
int mode = 0;
/*
mode = 1 for arming vehicle
mode = 2 for return to launch mode
mode = 3 for waiting mode
*/

unsigned long timer,loop_timer;
unsigned long prevtime, loop_prevtime;
unsigned long setup_time;

#include "GPRSfunctions.h"

/**************************************************************************************************************************/

#endif
