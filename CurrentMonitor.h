/**********************************************************************

CurrentMonitor.h
COPYRIGHT (c) 2013-2016 Gregg E. Berman

Part of DCC++ BASE STATION for the Arduino

**********************************************************************/

#ifndef CurrentMonitor_h
#define CurrentMonitor_h

#include "Arduino.h"

#define  CURRENT_SAMPLE_SMOOTHING   0.05
// Full Scale (1023) is 5V.  
// 2000mA current flow corresponds to 3.3V, i.e. sample value of 675.2
#define  CURRENT_SAMPLE_MAX_MAIN     337      // 1000mA 
#define  CURRENT_SAMPLE_MAX_PROG     67       // 200mA

// Sample every 1ms.
#ifdef ARDUINO_AVR_UNO                        // Configuration for UNO
  #define  CURRENT_SAMPLE_TIME        10
#else                                         // Configuration for MEGA    
  #define  CURRENT_SAMPLE_TIME        1
#endif

struct CurrentMonitor{
  static long int sampleTime;
  int pin;
  float current;
  int sample_max;
  const char *msg;
  CurrentMonitor(int, const char *, int);
  static boolean checkTime();
  void check();
};

#endif
