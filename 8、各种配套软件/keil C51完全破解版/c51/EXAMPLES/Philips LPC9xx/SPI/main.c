#include <Reg932.h> 

void WriteSPI (unsigned char dat)
{
  // write data to SPI bus
  SPDAT = dat;
  // wait for SPIF bit to be set
  while ((SPSTAT & 0x80) == 0)
  {
  }

  // Clear SPIF bit by writing 1 to it
  SPSTAT |= 0x80;
}


void main(void) 
{
  // Set Port 2 to quasi-bidirectional
  P2M1 = 0x00;  
  P2M2 = 0x00;

  // Initialize SPI
  SPCTL = 0xF7;

  while (1)
  {
    WriteSPI(0x11);
    WriteSPI(0x22);
    WriteSPI(0x44);
    WriteSPI(0x88);
  }
}

