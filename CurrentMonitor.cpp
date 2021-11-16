/**********************************************************************

CurrentMonitor.cpp
COPYRIGHT (c) 2013-2016 Gregg E. Berman

Part of DCC++ BASE STATION for the Arduino

Amended NMcK:
  Added sample_max to allow different current limit on main and programming tracks.

**********************************************************************/

#include "DCCpp_Uno.h"
#include "CurrentMonitor.h"

///////////////////////////////////////////////////////////////////////////////

CurrentMonitor::CurrentMonitor(int pin, const char *msg, int sample_max){
    this->pin=pin;
    this->msg=msg;
    this->sample_max=sample_max;
    current=0;
  } // CurrentMonitor::CurrentMonitor
  
boolean CurrentMonitor::checkTime(){
  unsigned long thisTime = millis();
  if(thisTime-sampleTime<CURRENT_SAMPLE_TIME)            // no need to check current yet
    return(false);
  sampleTime=thisTime;                                   // note millis() uses TIMER-0.  For UNO, we change the scale on Timer-0.  For MEGA we do not.  This means CURRENT_SAMPLE_TIME is different for UNO then MEGA
  return(true);  
} // CurrentMonitor::checkTime
  
void CurrentMonitor::check(){
  current=analogRead(pin)*CURRENT_SAMPLE_SMOOTHING+current*(1.0-CURRENT_SAMPLE_SMOOTHING);        // compute new exponentially-smoothed current
  if(current>sample_max /* && digitalRead(SIGNAL_ENABLE_PIN_MAIN)==HIGH */ ){                     // current overload and Prog Signal is on (or could have checked Main Signal, since both are always on or off together)
    digitalWrite(SIGNAL_ENABLE_PIN_PROG,LOW);                                                     // disable both Motor Shield Channels
    digitalWrite(SIGNAL_ENABLE_PIN_MAIN,LOW);                                                     // regardless of which caused current overload
    INTERFACE.print(msg);                                                                            // print corresponding error message
  }    
} // CurrentMonitor::check  

long int CurrentMonitor::sampleTime=0;
