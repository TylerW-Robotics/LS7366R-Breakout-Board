#include "SPI.h"

class LS7366R {
private:
  /* data */
protected:
  uint8_t ssPort;   // Saves port of encoder
  bool _reverseCheck;
public:
  long enCount;     // Records current count after encoder is read
  long enPrevCount; // Records count before a read count is read
  bool clearFlag;   // Checks if encoders was cleared

  LS7366R(int ss, bool reverseCheck = false) {
    enCount = 0;
    enPrevCount = 0;
    clearFlag = 1;
    ssPort = ss;
    _reverseCheck = reverseCheck;
    pinMode(ssPort, OUTPUT);
    digitalWrite(ssPort, 1);
  }
  void initEncoder();                               // Preps the encoder
  void initEncoderDev(uint8_t MDR0, uint8_t MDR1);  // Preps the encoder w/ user defined settings
  void readEncoder();                               // Stores Previous count and reads new count
  void clearEncoderCount();                         // Sets encoder chip & values to zero 
};