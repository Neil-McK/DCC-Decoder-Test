/**********************************************************************

PacketRegister.h
COPYRIGHT (c) 2013-2016 Gregg E. Berman

Part of DCC++ BASE STATION for the Arduino

**********************************************************************/

#ifndef PacketRegister_h
#define PacketRegister_h

#include "Arduino.h"

// Define constants used for reading CVs from the Programming Track

#define  ACK_BASE_COUNT            100      // number of analogRead samples to take before each CV verify to establish a baseline current
// One call to analogRead takes about 100uS, so 1000 samples corresponds to 100ms.
#define  ACK_SAMPLE_COUNT          1000     // number of analogRead samples to take when monitoring current after a CV verify (bit or byte) has been sent 
// Full Scale (1023) is 5V.  
// 2000mA current flow corresponds to 3.3V, i.e. sample value of 675.2 and 60mA corresponds to 20 and 45mA is 15.
#define  ACK_SAMPLE_THRESHOLD       15      // the threshold that the analogRead samples (after subtracting the baseline current) must cross to establish ACKNOWLEDGEMENT

// Define a series of registers that can be sequentially accessed over a loop to generate a repeating series of DCC Packets

struct Packet{
  byte buf[10];
  byte nBits;
}; // Packet

struct Register{
  Packet packet[2];
  Packet *activePacket;
  Packet *updatePacket;
  void initPackets();
}; // Register
  
struct RegisterList{  
  int maxNumRegs;
  Register *reg;
  Register **regMap;
  Register *currentReg;
  Register *maxLoadedReg;
  Register *nextReg;
  Packet  *tempPacket;
  byte currentBit;
  byte nRepeat;
  int *speedTable;
  int baseCurrent;
  byte ackReceived;
  static byte idlePacket[];
  static byte resetPacket[];
  static byte bitMask[];
  RegisterList(int);
  void loadPacket(int, byte *, int, int, int=0) volatile;
  void setThrottle(char *) volatile;
  void setFunction(char *) volatile;  
  void setAccessory(char *) volatile;
  void writeTextPacket(char *) volatile;
  void readCV(char *) volatile;
  void writeCVByte(char *) volatile;
  void writeCVBit(char *) volatile;
  void writeCVByteMain(char *) volatile;
  void writeCVBitMain(char *s) volatile;  
  void printPacket(int, byte *, int, int) volatile;
  void prepareForAck() volatile;
  void checkForAck() volatile;
};

#endif
