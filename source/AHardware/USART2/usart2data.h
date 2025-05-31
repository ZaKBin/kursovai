#ifndef USART2DATA
#define USART2DATA

#include "usart2fieldvalues.hpp" // for USART2
#include "usart2registers.hpp" // for USART2
#include <sstream>

class Usart2Data
{
public:
  void WriteData(std::float_t value)
  {
    sReceivedValue = {"Voltage: " + ToStringWithPrecision(value) + " V" +"\n"};
    while(i < sReceivedValue.length())
    {
      while(!USART2::SR::TXE::DataRegisterEmpty::IsSet()) {}
      USART2::DR::Write(sReceivedValue[i++]);
    }
    i = 0;
  }
private:
  std::string sReceivedValue;
  std::size_t i = 0;
  std::string ToStringWithPrecision(const std::float_t a_value, const int n = 2)
  {
   std::ostringstream out;
   out.precision(n);
   out << std::fixed << a_value;
   return std::move(out).str();
  }
};

#endif