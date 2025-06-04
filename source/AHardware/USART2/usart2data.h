#ifndef USART2DATA
#define USART2DATA

#include "usart2fieldvalues.hpp" // for USART2
#include "usart2registers.hpp" // for USART2
#include <sstream>

class Usart2Data
{
public:
  void WriteData(const char* message)
  {
    if (mBufferLength != 0)
    {
        return;
    }

    std::size_t len = std::strlen(message);
    if (len >= mBufferCapacity)
    {
        len = mBufferCapacity - 1;
    }
    std::memcpy(mBuffer, message, len);
    mBuffer[len] = '\0';

    mBufferLength = len;
 

    while(mIndex < mBufferLength)
    {
      while(!USART2::SR::TXE::DataRegisterEmpty::IsSet()) {}
      USART2::DR::Write(mBuffer[mIndex++]);
    }
    mBufferLength = 0;
       mIndex = 0;
  }
private:
  static constexpr std::size_t mBufferCapacity = 128;
  char mBuffer[mBufferCapacity];
  std::size_t mBufferLength;
  std::size_t mIndex;
};

#endif