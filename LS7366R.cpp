#include "LS7366R.h"
#include "Arduino.h"
#include "SPI.h"

void LS7366R::initEncoder() {
  
  // init encoder
  digitalWrite(ssPort, 0); // Start Communication
  SPI.transfer(0x88);   // Write to MDR0
  SPI.transfer(0x03);   // Write to MDR1
  digitalWrite(ssPort, 1); // End Communication

  /*
  MDR0:
      B1 B0 = 00: non-quadrature count mode. (A = clock, B = direction).
            = 01: x1 quadrature count mode (one count per quadrature cycle).
            = 10: x2 quadrature count mode (two counts per quadrature cycle).
            = 11: x4 quadrature count mode (four counts per quadrature cycle).
      B3 B2 = 00: free-running count mode.
            = 01: single-cycle count mode (counter disabled with carry or borrow, re-enabled with reset or load).
            = 10: range-limit count mode (up and down count-ranges are limited between DTR and zero,
                    respectively; counting freezes at these limits but resumes when direction reverses).
            = 11: modulo-n count mode (input count clock frequency is divided by a factor of (n+1),
                    where n = DTR, in both up and down directions).
      B5 B4 = 00: disable index.
            = 01: configure index as the "load CNTR" input (transfers DTR to CNTR).
            = 10: configure index as the "reset CNTR" input (clears CNTR to 0).
            = 11: configure index as the "load OTR" input (transfers CNTR to OTR).
      B6 = 0: Asynchronous Index
         = 1: Synchronous Index (overridden in non-quadrature mode)
      B7 = 0: Filter clock division factor = 1
         = 1: Filter clock division factor = 2
  
  MDR1:
      B1 B0 = 00: 4-byte counter mode
            = 01: 3-byte counter mode
            = 10: 2-byte counter mode.
            = 11: 1-byte counter mode
      B2 = 0: Enable counting
         = 1: Disable counting
      B3 = : not used
      B4 = 0: NOP
         = 1: FLAG on IDX (B4 of STR)
      B5 = 0: NOP
         = 1: FLAG on CMP (B5 of STR)
      B6 = 0: NOP
         = 1: FLAG on BW (B6 of STR)
      B7 = 0: NOP
         = 1: FLAG on CY (B7 of STR

  */
  

}

void LS7366R::initEncoderDev(uint8_t MDR0, uint8_t MDR1) {
  
  // init encoder
  digitalWrite(ssPort, 0); // Start Communication
  SPI.transfer(MDR0);   // Write to MDR0
  SPI.transfer(MDR1);   // Write to MDR1
  digitalWrite(ssPort, 1); // End Communication

  /*
  MDR0:
      B1 B0 = 00: non-quadrature count mode. (A = clock, B = direction).
            = 01: x1 quadrature count mode (one count per quadrature cycle).
            = 10: x2 quadrature count mode (two counts per quadrature cycle).
            = 11: x4 quadrature count mode (four counts per quadrature cycle).
      B3 B2 = 00: free-running count mode.
            = 01: single-cycle count mode (counter disabled with carry or borrow, re-enabled with reset or load).
            = 10: range-limit count mode (up and down count-ranges are limited between DTR and zero,
                    respectively; counting freezes at these limits but resumes when direction reverses).
            = 11: modulo-n count mode (input count clock frequency is divided by a factor of (n+1),
                    where n = DTR, in both up and down directions).
      B5 B4 = 00: disable index.
            = 01: configure index as the "load CNTR" input (transfers DTR to CNTR).
            = 10: configure index as the "reset CNTR" input (clears CNTR to 0).
            = 11: configure index as the "load OTR" input (transfers CNTR to OTR).
      B6 = 0: Asynchronous Index
         = 1: Synchronous Index (overridden in non-quadrature mode)
      B7 = 0: Filter clock division factor = 1
         = 1: Filter clock division factor = 2
  
  MDR1:
      B1 B0 = 00: 4-byte counter mode
            = 01: 3-byte counter mode
            = 10: 2-byte counter mode.
            = 11: 1-byte counter mode
      B2 = 0: Enable counting
         = 1: Disable counting
      B3 = : not used
      B4 = 0: NOP
         = 1: FLAG on IDX (B4 of STR)
      B5 = 0: NOP
         = 1: FLAG on CMP (B5 of STR)
      B6 = 0: NOP
         = 1: FLAG on BW (B6 of STR)
      B7 = 0: NOP
         = 1: FLAG on CY (B7 of STR

  */
  

}

void LS7366R::readEncoder() {
  // Storing Previous Count
  enPrevCount = enCount;

  // Temporary Value
  long count_value;  

  // Read encoder
  digitalWrite(ssPort, 0);      // Begin SPI conversation
  SPI.transfer(0x60);                     // Request count

  // Collect 4 bytes to construct the long encoder value
  count_value = SPI.transfer(0x00);       
  count_value = (count_value << 8) + SPI.transfer(0x00);
  count_value = (count_value << 8) + SPI.transfer(0x00);
  count_value = (count_value << 8) + SPI.transfer(0x00);
  digitalWrite(ssPort, 1);     // Terminate SPI conversation 

  enCount = count_value;
}

void LS7366R::clearEncoderCount() {
  enCount = 0;
  enPrevCount = 0;
  // Set encoder1's data register to 0
  digitalWrite(ssPort, 0);      // Begin SPI conversation  
  // Write to DTR
  SPI.transfer(0x98);    
  // Load data
  SPI.transfer(0x00);  // Highest order byte
  SPI.transfer(0x00);           
  SPI.transfer(0x00);           
  SPI.transfer(0x00);  // lowest order byte
  digitalWrite(ssPort, 1);     // Terminate SPI conversation 

  delayMicroseconds(100);  // provides some breathing room between SPI conversations
  
  // Set encoder's current data register to center
  digitalWrite(ssPort, 0);      // Begin SPI conversation  
  SPI.transfer(0xE0);    
  digitalWrite(ssPort, 1);     // Terminate SPI conversation   
   
}