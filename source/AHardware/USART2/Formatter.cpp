#include "Formatter.h" // for Formatter
#include <string> // for std::snprintf

Formatter :: Formatter() : mPrefix(nullptr)
{}

char* Formatter :: FormatString(std::float_t value, const uint8_t precision, const char* unit)
{
  mPrefix = "Voltage: ";
  
  std::snprintf(mBuffer, sizeof(mBuffer), "%s%.*f%s\r", mPrefix, precision, static_cast<double>(value), unit);
      
  return mBuffer;
}