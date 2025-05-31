#ifndef IFILTER
#define IFILTER

class IFilter
{
public:
  
  virtual std::float_t FilterValue(std::float_t value) = 0;
};

#endif