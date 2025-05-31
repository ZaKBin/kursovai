#ifndef IFILTERNOTIFIER
#define IFILTERNOTIFIER

class IFilterNotifier
{
public:
  
  virtual void FilteredValueUpdate(std::float_t value) = 0;
};

#endif