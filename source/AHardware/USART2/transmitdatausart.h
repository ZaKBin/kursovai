#ifndef TRANSMITDATAUSART
#define TRANSMITDATAUSART

#include "usart2data.h" // for USART2

class TransmitDataUsart
{
public:
  TransmitDataUsart(Usart2Data& usart2) : mUsart2(usart2)
  {
    
  }
  
  void WriteData(std::float_t value)
  {
    mUsart2.WriteData(value);
  }
private:
  Usart2Data& mUsart2;
};

#endif