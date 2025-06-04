#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include "IFormatter.h" // for IFormatter

class Formatter : public IFormatter
{
public:
  Formatter();
  char* FormatString(std::float_t value, const uint8_t precision, const char* unit) override;
private:
  char mBuffer[250];
  const char* mPrefix;
};

#endif