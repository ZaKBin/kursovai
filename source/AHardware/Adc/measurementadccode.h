#ifndef MEASUREMENTADCCODE
#define MEASUREMENTADCCODE

#include <iintdataprovider.h> // for ADC

class MeasurementADCCode : public IIntDataProvider
{
public:
  std::uint16_t ReadData() const override
  {
    ADC1::CR2::SWSTART::On::Set();
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {
      
    }
    return static_cast<std::uint16_t>(ADC1::DR::DATA::Get());
  }
};

#endif