#ifndef IFORMATTER_HPP
#define IFORMATTER_HPP
#include <cstdint> // for std::uint8_t
#include <cmath>

class IFormatter
{
public:
  virtual char* FormatString(std::float_t value, const uint8_t precision, const char* unit) = 0;
};

#endif