#ifndef FILTER
#define FILTER

#include "ifilter.h" // for IFilter

template<const std::float_t& dt, const std::float_t& rc>
class Filter : public IFilter
{
public:
  std::float_t FilterValue(std::float_t value) override
  {
    static bool isFirstTime = true;
    if(isFirstTime)
    {
      oldValue = value;
      return value;
    }
    auto filteredValue = oldValue + (value - oldValue) * tau;
    oldValue = filteredValue;
    return filteredValue;
  }
private:
  std::float_t oldValue;
  const std::float_t tau = 1.0f - exp(-dt/rc);
  };

#endif
