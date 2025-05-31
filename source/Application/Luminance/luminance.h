#ifndef LUMINANCE
#define LUMINANCE

#include <iluminance.h> // for Iluminance
#include <ipwm.h> // for IPwm

template<const float& maxVoltageValue>
class Luminance : public ILuminance
{
public:
  Luminance(IPwm& pwm) : mPwm(pwm)
  {
    
  }
  
  void Update(std::float_t filtredValue) override
  {
    std::float_t kz = filtredValue/maxVoltageValue;
    mPwm.SetValue(kz);
  }
private:
  IPwm& mPwm;
};

#endif