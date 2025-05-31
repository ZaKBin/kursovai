#ifndef VOLTAGE
#define VOLTAGE

#include <iparametr.h> //for IParametr
#include <iintdataprovider.h> //for IIntDataProvider

template<const float& k, const float& offset>
class Voltage : public IParametr
{
public:
  Voltage(IIntDataProvider& adc) : mADC(adc)
  {
    
  }
  
  float Measure() override
  {
    return (k*(static_cast<float>(mADC.ReadData())) + offset);
  }
private:
  IIntDataProvider& mADC;
};

#endif